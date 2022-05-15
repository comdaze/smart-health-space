/*
 * Smart Health Space (based on AWS IoT EduKit - Core2 for AWS IoT EduKit)
 * main.c
 * 
 * Copyright 2010-2022 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Additions Copyright 2016 Espressif Systems (Shanghai) PTE LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */
/**
 * @file main.c
 * @brief simple MQTT publish, subscribe, and device shadows for use with AWS IoT EduKit reference hardware.
 *
 * This example takes the parameters from the build configuration and establishes a connection to AWS IoT Core over MQTT.
 *
 * Some configuration is required. Visit https://edukit.workshop.aws
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"
#include "esp_log.h"

#include "aws_iot_config.h"
#include "aws_iot_log.h"
#include "aws_iot_version.h"
#include "aws_iot_mqtt_client_interface.h"
#include "aws_iot_shadow_interface.h"

#include "core2forAWS.h"

#include "wifi.h"
#include "fft.h"
#include "ui.h"
#include "driver/uart.h"
#include "driver/gpio.h"

static const char *TAG = "MAIN";

#define MAX_LENGTH_OF_UPDATE_JSON_BUFFER 500
#define GPIO_PIR GPIO_NUM_26

/* CA Root certificate */
extern const uint8_t aws_root_ca_pem_start[] asm("_binary_aws_root_ca_pem_start");
extern const uint8_t aws_root_ca_pem_end[] asm("_binary_aws_root_ca_pem_end");

/* Default MQTT HOST URL is pulled from the aws_iot_config.h */
char HostAddress[255] = AWS_IOT_MQTT_HOST;

/* Default MQTT port is pulled from the aws_iot_config.h */
uint32_t port = AWS_IOT_MQTT_PORT;

TaskHandle_t led_bar_blink_handle;

bool startUp = true; // flag to run 1st connection upon startup
char temp_str[200];

char temp_str_awsCount[200];
char temp_str_awsPIR[200];

// *** json variable for mqtt ***********************************************************************


bool pir_detected  = false;

uint16_t count_fr_aws = 0;

char *iot_topic = "detect/mask";

// *** iot callback handler ***********************************************************************
void iot_subscribe_callback_handler(AWS_IoT_Client *pClient, char *topicName, uint16_t topicNameLen,
                                    IoT_Publish_Message_Params *params, void *pData) {
    ESP_LOGI(TAG, "Subscribe callback");
    ESP_LOGI(TAG, "%.*s\t%.*s", topicNameLen, topicName, (int) params->payloadLen, (char *)params->payload);
}

void disconnect_callback_handler(AWS_IoT_Client *pClient, void *data) {
    ESP_LOGW(TAG, "MQTT Disconnect");
    ui_textarea_add("Disconnected from AWS IoT Core...", NULL, 0);

    IoT_Error_t rc = FAILURE;

    if(NULL == pClient) {
        return;
    }

    if(aws_iot_is_autoreconnect_enabled(pClient)) {
        ESP_LOGI(TAG, "Auto Reconnect is enabled, Reconnecting attempt will start now");
    } else {
        ESP_LOGW(TAG, "Auto Reconnect not enabled. Starting manual reconnect...");
        rc = aws_iot_mqtt_attempt_reconnect(pClient);
        if(NETWORK_RECONNECTED == rc) {
            ESP_LOGW(TAG, "Manual Reconnect Successful");
        } else {
            ESP_LOGW(TAG, "Manual Reconnect Failed - %d", rc);
        }
    }
}

static bool shadowUpdateInProgress;

void ShadowUpdateStatusCallback(const char *pThingName, ShadowActions_t action, Shadow_Ack_Status_t status,
                                const char *pReceivedJsonDocument, void *pContextData) {
    IOT_UNUSED(pThingName);
    IOT_UNUSED(action);
    IOT_UNUSED(pReceivedJsonDocument);
    IOT_UNUSED(pContextData);

    shadowUpdateInProgress = false;

    if(SHADOW_ACK_TIMEOUT == status) {
        ESP_LOGE(TAG, "Update timed out");
    } else if(SHADOW_ACK_REJECTED == status) {
        ESP_LOGE(TAG, "Update rejected");
    } else if(SHADOW_ACK_ACCEPTED == status) {
        ESP_LOGI(TAG, "Update accepted");
    }
}

// *** state callback handler ******************************************************************

void awsCount_Callback(const char *pJsonString, uint32_t JsonStringDataLen, jsonStruct_t *pContext) {
    IOT_UNUSED(pJsonString);
    IOT_UNUSED(JsonStringDataLen);

    if(pContext != NULL) {
        ESP_LOGI(TAG, "Delta - count_fr_aws number changed to %d", *(uint16_t *) (pContext->pData));
        sprintf(temp_str_awsCount, "Counter: %d", *(uint16_t *) (pContext->pData));
        ui_awsCount_lab(temp_str_awsCount);
    }
}

void awsPIR_Callback(const char *pJsonString, uint32_t JsonStringDataLen, jsonStruct_t *pContext) {
    IOT_UNUSED(pJsonString);
    IOT_UNUSED(JsonStringDataLen);

    if(pContext != NULL) {
        ESP_LOGI(TAG, "Delta - pir_detected changed to %d", *(bool *) (pContext->pData));
        sprintf(temp_str_awsPIR, "Detected: %d", *(bool *) (pContext->pData));
        ui_awsPIR_lab(temp_str_awsPIR);
    }
}


// *** aws iot task ***********************************************************************

void aws_iot_task(void *param) {
    IoT_Error_t rc = FAILURE;

    char JsonDocumentBuffer[MAX_LENGTH_OF_UPDATE_JSON_BUFFER];
    size_t sizeOfJsonDocumentBuffer = sizeof(JsonDocumentBuffer) / sizeof(JsonDocumentBuffer[0]);
    

    ESP_LOGI(TAG, "AWS IoT SDK Version %d.%d.%d-%s", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_TAG);

    // initialize the mqtt client
    AWS_IoT_Client iotCoreClient;

	IoT_Client_Init_Params mqttInitParams = iotClientInitParamsDefault;
    mqttInitParams.enableAutoReconnect = false; // We enable this later below
	mqttInitParams.pHostURL = HostAddress;
	mqttInitParams.port = port;
	mqttInitParams.pRootCALocation = (const char *)aws_root_ca_pem_start;
	mqttInitParams.pDeviceCertLocation = "#";
	mqttInitParams.pDevicePrivateKeyLocation = "#0";
	mqttInitParams.mqttCommandTimeout_ms = 20000;
	mqttInitParams.tlsHandshakeTimeout_ms = 5000;
	mqttInitParams.isSSLHostnameVerify = true;
	mqttInitParams.disconnectHandler = disconnect_callback_handler;
	mqttInitParams.disconnectHandlerData = NULL;


    #define CLIENT_ID_LEN (ATCA_SERIAL_NUM_SIZE * 2)
    char *client_id = malloc(CLIENT_ID_LEN + 1);
    ATCA_STATUS ret = Atecc608_GetSerialString(client_id);
    if (ret != ATCA_SUCCESS){
        ESP_LOGE(TAG, "Failed to get device serial from secure element. Error: %i", ret);
        abort();
    }

    ui_textarea_add("\nDevice client Id:\n>> %s <<\n", client_id, CLIENT_ID_LEN);

    /* Wait for WiFI to show as connected */
    xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT,
                        false, true, portMAX_DELAY);

    
    
    ESP_LOGI(TAG, "MQTT Init");

	IoT_Client_Connect_Params connectParams = iotClientConnectParamsDefault;
	connectParams.keepAliveIntervalInSec = 600;
	connectParams.isCleanSession = true;
	connectParams.MQTTVersion = MQTT_3_1_1;
	connectParams.pClientID = AWS_IOT_MQTT_CLIENT_ID;
	connectParams.clientIDLen = (uint16_t) strlen(AWS_IOT_MQTT_CLIENT_ID);
	connectParams.isWillMsgPresent = false;

	rc = aws_iot_mqtt_init(&iotCoreClient, &mqttInitParams);
	if(SUCCESS != rc) {
		IOT_ERROR("aws_iot_mqtt_init returned error : %d ", rc);
		abort();
	}


	IOT_INFO("Connecting...");
	rc = aws_iot_mqtt_connect(&iotCoreClient, &connectParams);
	if(SUCCESS != rc) {
		IOT_ERROR("Error(%d) connecting to %s:%d", rc, mqttInitParams.pHostURL, mqttInitParams.port);
		abort();
	}

	rc = aws_iot_mqtt_autoreconnect_set_status(&iotCoreClient, true);
	if(SUCCESS != rc) {
		IOT_ERROR("Unable to set Auto Reconnect to true - %d", rc);
		abort();
	}

	IOT_INFO("Subscribing...");
	rc = aws_iot_mqtt_subscribe(&iotCoreClient, iot_topic, 11, QOS0, iot_subscribe_callback_handler, NULL);
	if(SUCCESS != rc) {
		IOT_ERROR("Error subscribing : %d ", rc);
		abort();
	}


    // initialize the device shadow

    // *** json variable ***********************************************************************

    jsonStruct_t testHandler_pir_detector;
    testHandler_pir_detector.cb = awsPIR_Callback;
    testHandler_pir_detector.pKey = "pir_detected";
    testHandler_pir_detector.pData = &pir_detected;
    testHandler_pir_detector.type = SHADOW_JSON_BOOL;
    testHandler_pir_detector.dataLength = sizeof(bool);


    jsonStruct_t awsCount;
    awsCount.cb = awsCount_Callback;
    awsCount.pKey = "count_fr_aws";
    awsCount.pData = &count_fr_aws;
    awsCount.type = SHADOW_JSON_UINT16;
    awsCount.dataLength = sizeof(uint16_t);

   // *** Shadow init Parameters Definition***********************************************************************
    ShadowInitParameters_t sp = ShadowInitParametersDefault;
    sp.pHost = HostAddress;
    sp.port = port;
    sp.enableAutoReconnect = false;
    sp.disconnectHandler = disconnect_callback_handler;

    sp.pRootCA = (const char *)aws_root_ca_pem_start;
    sp.pClientCRT = "#";
    sp.pClientKey = "#0";

    
    ESP_LOGI(TAG, "Shadow Init");

    rc = aws_iot_shadow_init(&iotCoreClient, &sp);
    if(SUCCESS != rc) {
        ESP_LOGE(TAG, "aws_iot_shadow_init returned error %d, aborting...", rc);
        abort();
    }

    ShadowConnectParameters_t scp = ShadowConnectParametersDefault;
    scp.pMyThingName = client_id;
    scp.pMqttClientId = client_id;
    scp.mqttClientIdLen = CLIENT_ID_LEN;

    ESP_LOGI(TAG, "Shadow Connect");
    rc = aws_iot_shadow_connect(&iotCoreClient, &scp);
    if(SUCCESS != rc) {
        ESP_LOGE(TAG, "aws_iot_shadow_connect returned error %d, aborting...", rc);
        abort();
    }
    ui_wifi_label_update(true); // Switch wifi label to green color
    ui_textarea_add("\nConnected to AWS IoT Core and pub/sub to the device shadow state\n", NULL, 0);

    rc = aws_iot_shadow_set_autoreconnect_status(&iotCoreClient, true);
    if(SUCCESS != rc) {
        ESP_LOGE(TAG, "Unable to set Auto Reconnect to true - %d, aborting...", rc);
        abort();
    }

    // *** register delta callback  ***************************************************************

    rc = aws_iot_shadow_register_delta(&iotCoreClient, &awsCount);
    if(SUCCESS != rc) {
        ESP_LOGE(TAG, "Shadow Register Delta Error");
    }
    rc = aws_iot_shadow_register_delta(&iotCoreClient, &testHandler_pir_detector);
    if(SUCCESS != rc) {
        ESP_LOGE(TAG, "Shadow Register Delta Error");
    }
    // loop and publish changes
    while(NETWORK_ATTEMPTING_RECONNECT == rc || NETWORK_RECONNECTED == rc || SUCCESS == rc) {
        rc = aws_iot_shadow_yield(&iotCoreClient, 500);
        if(NETWORK_ATTEMPTING_RECONNECT == rc || shadowUpdateInProgress) {
            rc = aws_iot_shadow_yield(&iotCoreClient, 1000);
            // If the client is attempting to reconnect, or already waiting on a shadow update,
            // we will skip the rest of the loop.
            continue;
        }
        // *** Test ***********************************************************************
        ESP_LOGI(TAG, "Just a trigger to see if connection is alive.....................");

        if (startUp == true || pir_detected ==false || pir_detected == true ){

            ESP_LOGI(TAG, "*****************************************************************************************");
            // *** json variable ***********************************************************************
            //ESP_LOGI(TAG, "On Device: pir_detector %s", pir_detected ? "true" : "false");
           
            //ESP_LOGI(TAG, "On Device: count_fr_aws    \t%d", count_fr_aws);
            sprintf(temp_str, "DETECTING...");     
            ui_textlabel_add(temp_str);
            rc = aws_iot_shadow_init_json_document(JsonDocumentBuffer, sizeOfJsonDocumentBuffer);
            
            if(SUCCESS == rc) {
               rc = aws_iot_shadow_add_reported(JsonDocumentBuffer, sizeOfJsonDocumentBuffer, 2,
                                                &testHandler_pir_detector, &awsCount);
                if(SUCCESS == rc) {
                    rc = aws_iot_finalize_json_document(JsonDocumentBuffer, sizeOfJsonDocumentBuffer);
                    if(SUCCESS == rc) {
                        ESP_LOGI(TAG, "Update Shadow: %s", JsonDocumentBuffer);
                        rc = aws_iot_shadow_update(&iotCoreClient, client_id, JsonDocumentBuffer,
                                                ShadowUpdateStatusCallback, NULL, 6, true);
                        shadowUpdateInProgress = true;
                    }
                }
            }
            // Subscribe a iot_topic
            aws_iot_mqtt_subscribe(&iotCoreClient, iot_topic, 11, QOS0, iot_subscribe_callback_handler, NULL);

            ESP_LOGI(TAG, "*****************************************************************************************");
            ESP_LOGI(TAG, "Stack remaining for task '%s' is %d bytes", pcTaskGetTaskName(NULL), uxTaskGetStackHighWaterMark(NULL));
            
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }

    if(SUCCESS != rc) {
        ESP_LOGE(TAG, "An error occurred in the loop %d", rc);
    }

    ESP_LOGI(TAG, "Disconnecting");
    rc = aws_iot_shadow_disconnect(&iotCoreClient);

    if(SUCCESS != rc) {
        ESP_LOGE(TAG, "Disconnect error %d", rc);
    }

    vTaskDelete(NULL);
}


// *** PIR sensor at portB ******************************************************************

void readInputTask(){ 
    bool pir_curr = false;
    int pir_count = 0;
    for(;;){
        pir_curr = Core2ForAWS_Port_Read(GPIO_PIR);
        if (pir_curr == true){
            pir_detected = true;
            //ESP_LOGI(TAG, "PIR sensor detected!"); 
            sprintf(temp_str_awsPIR, "Detected: true");
            ui_awsPIR_lab(temp_str_awsPIR);
            //ESP_LOGI(TAG, "set side LEDs to red");
            Core2ForAWS_Sk6812_SetSideColor(SK6812_SIDE_LEFT, 0xFF0000);
            Core2ForAWS_Sk6812_SetSideColor(SK6812_SIDE_RIGHT, 0xFF0000);
            Core2ForAWS_Sk6812_Show();

            pir_count++;   
            count_fr_aws = pir_count;
            ESP_LOGI(TAG, "Delta - count_fr_aws number changed to %d", count_fr_aws);
            sprintf(temp_str_awsCount, "Counter: %d", count_fr_aws);
            ui_awsCount_lab(temp_str_awsCount);
            //ESP_LOGI(TAG, "PIR sensor counted!"); 
        } else {
            pir_detected = false;
            sprintf(temp_str_awsPIR, "Detected: false");
            ui_awsPIR_lab(temp_str_awsPIR);
            //ESP_LOGI(TAG, "clearing side LEDs");
            Core2ForAWS_Sk6812_Clear();
            Core2ForAWS_Sk6812_Show();
            }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}


void app_main()
{   
    ESP_LOGI(TAG, "\n***************************************************\nHealthy Spaces Checker\n***************************************************");
    Core2ForAWS_Init();
    Core2ForAWS_Display_SetBrightness(50);

    ui_init();
    initialise_wifi();
    xTaskCreatePinnedToCore(&aws_iot_task, "aws_iot_task", 4096*2, NULL, 5, NULL, 1);
   
    esp_err_t err_GPIO_PIR = Core2ForAWS_Port_PinMode(GPIO_PIR, INPUT);
    if(err_GPIO_PIR == ESP_OK){
        xTaskCreatePinnedToCore(readInputTask, "read_pin", 1024*4, NULL, 1, NULL, 1);
    }
  
    vTaskSuspend(led_bar_blink_handle);
}