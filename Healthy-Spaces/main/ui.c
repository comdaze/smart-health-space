/*
 * Smart Health Space (based on AWS IoT EduKit - Core2 for AWS IoT EduKit)
 * ui.c
 * 
 * Copyright (C) 2022 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

#include "esp_log.h"
#include "core2forAWS.h"
#include "ui.h"

#define MAX_TEXTAREA_LENGTH 1024

static lv_obj_t *active_screen;
static lv_obj_t *out_txtarea;
static lv_obj_t *wifi_label;

static lv_style_t bg_style;
static lv_obj_t* screen_bg;
static lv_obj_t* temp_label;

static lv_obj_t* awsPIR_obj;
static lv_obj_t* awsCount_obj;

static lv_obj_t* awsPIR_lab;
static lv_obj_t* awsCount_lab;

static char *TAG = "UI";

TaskHandle_t power_handle;

static void ui_textarea_prune(size_t new_text_length){
    const char * current_text = lv_textarea_get_text(out_txtarea);
    size_t current_text_len = strlen(current_text);
    if(current_text_len + new_text_length >= MAX_TEXTAREA_LENGTH){
        for(int i = 0; i < new_text_length; i++){
            lv_textarea_set_cursor_pos(out_txtarea, 0);
            lv_textarea_del_char_forward(out_txtarea);
        }
        lv_textarea_set_cursor_pos(out_txtarea, LV_TEXTAREA_CURSOR_LAST);
    }
}

void ui_textarea_add(char *baseTxt, char *param, size_t paramLen) {
    if( baseTxt != NULL ){
        xSemaphoreTake(xGuiSemaphore, portMAX_DELAY);
        if (param != NULL && paramLen != 0){
            size_t baseTxtLen = strlen(baseTxt);
            ui_textarea_prune(paramLen);
            size_t bufLen = baseTxtLen + paramLen;
            char buf[(int) bufLen];
            sprintf(buf, baseTxt, param);
            lv_textarea_add_text(out_txtarea, buf);
        } 
        else{
            lv_textarea_add_text(out_txtarea, baseTxt); 
        }
        xSemaphoreGive(xGuiSemaphore);
    } 
    else{
        ESP_LOGE(TAG, "Textarea baseTxt is NULL!");
    }
}

void ui_wifi_label_update(bool state){
    xSemaphoreTake(xGuiSemaphore, portMAX_DELAY);
    if (state == false) {
        lv_label_set_text(wifi_label, LV_SYMBOL_WIFI);
    } 
    else{
        char buffer[25];
        //sprintf (buffer, "#0000ff %s #", LV_SYMBOL_WIFI);
        sprintf (buffer, "#0ab300 %s #", LV_SYMBOL_WIFI);
        lv_label_set_text(wifi_label, buffer);
    }
    xSemaphoreGive(xGuiSemaphore);
}

void ui_textlabel_add(char *baseTxt) {
    xSemaphoreTake(xGuiSemaphore, portMAX_DELAY);
    if( baseTxt != NULL ) {
        lv_label_set_text(temp_label, baseTxt);
        lv_obj_align(temp_label, screen_bg, LV_ALIGN_CENTER, 0, 40);
    } else {
        lv_label_set_text(temp_label, "");
    }
    xSemaphoreGive(xGuiSemaphore);
}

void ui_awsPIR_lab(char *baseTxt) {
    xSemaphoreTake(xGuiSemaphore, portMAX_DELAY);
    if( baseTxt != NULL ) {
        lv_label_set_text(awsPIR_lab, baseTxt);
        lv_obj_align(awsPIR_lab, awsPIR_obj, LV_ALIGN_IN_TOP_MID, 0, 10);
    } 
    xSemaphoreGive(xGuiSemaphore);
}

void ui_awsCount_lab(char *baseTxt) {
    xSemaphoreTake(xGuiSemaphore, portMAX_DELAY);
    if( baseTxt != NULL ) {
        lv_label_set_text(awsCount_lab, baseTxt);
        lv_obj_align(awsCount_lab, awsCount_obj, LV_ALIGN_IN_TOP_MID, 0, 10);
    } 
    xSemaphoreGive(xGuiSemaphore);
    
}

void battery_task(void* pvParameters){
    xSemaphoreTake(xGuiSemaphore, portMAX_DELAY);
    lv_obj_t* battery_label = lv_label_create((lv_obj_t*)pvParameters, NULL);
    lv_label_set_text(battery_label, LV_SYMBOL_BATTERY_FULL);
    lv_label_set_recolor(battery_label, true);
    lv_label_set_align(battery_label, LV_LABEL_ALIGN_CENTER);
    lv_obj_align(battery_label, (lv_obj_t*)pvParameters, LV_ALIGN_IN_TOP_RIGHT,-8, 7);
    lv_obj_t* charge_label = lv_label_create(battery_label, NULL);
    lv_label_set_recolor(charge_label, true);
    lv_label_set_text(charge_label, "");
    lv_obj_align(charge_label, battery_label, LV_ALIGN_CENTER, -4, 1);
    xSemaphoreGive(xGuiSemaphore);

    for(;;){
        xSemaphoreTake(xGuiSemaphore, portMAX_DELAY);
        float battery_voltage = Core2ForAWS_PMU_GetBatVolt();
        if(battery_voltage >= 4.100){
            lv_label_set_text(battery_label, "#0ab300 " LV_SYMBOL_BATTERY_FULL "#");
        } else if(battery_voltage >= 3.95){
            lv_label_set_text(battery_label, "#0ab300 " LV_SYMBOL_BATTERY_3 "#");
        } else if(battery_voltage >= 3.80){
            lv_label_set_text(battery_label, "#ff9900 " LV_SYMBOL_BATTERY_2 "#");
        } else if(battery_voltage >= 3.25){
            lv_label_set_text(battery_label, "#ff0000 " LV_SYMBOL_BATTERY_1 "#");
        } else{
            lv_label_set_text(battery_label, "#ff0000 " LV_SYMBOL_BATTERY_EMPTY "#");
        }

        if(Core2ForAWS_PMU_GetBatCurrent() >= 0.00){
            lv_label_set_text(charge_label, "#0000cc " LV_SYMBOL_CHARGE "#");
        } else{
            lv_label_set_text(charge_label, "");
        }
        xSemaphoreGive(xGuiSemaphore);
        vTaskDelay(pdMS_TO_TICKS(200));
    }

    vTaskDelete(NULL); // Should never get to here...
}

void ui_init() {
    xSemaphoreTake(xGuiSemaphore, portMAX_DELAY);
    active_screen = lv_scr_act();
    wifi_label = lv_label_create(active_screen, NULL);
    lv_obj_align(wifi_label,NULL,LV_ALIGN_IN_TOP_RIGHT, -20, 6);
    lv_label_set_text(wifi_label, LV_SYMBOL_WIFI);
    lv_label_set_recolor(wifi_label, true);

    /* Create the main body object and set background within the tab*/
    screen_bg = lv_obj_create(active_screen, NULL);
    lv_obj_align(screen_bg, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 30);
    lv_obj_set_size(screen_bg, 300, 40);
    lv_obj_set_click(screen_bg, false);
    lv_style_init(&bg_style);
    lv_style_set_bg_color(&bg_style, LV_STATE_DEFAULT, lv_color_make(0, 100, 200));
    lv_obj_add_style(screen_bg, LV_OBJ_PART_MAIN, &bg_style);

    /* Create the title within the main body object */
    static lv_style_t title_style;
    lv_style_init(&title_style);
    lv_style_set_text_font(&title_style, LV_STATE_DEFAULT, LV_THEME_DEFAULT_FONT_TITLE);
    lv_style_set_text_color(&title_style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_t* tab_title_label = lv_label_create(screen_bg, NULL);
    lv_obj_add_style(tab_title_label, LV_OBJ_PART_MAIN, &title_style);
    lv_label_set_static_text(tab_title_label, "Healthy Spaces Checker");
    lv_obj_align(tab_title_label, screen_bg, LV_ALIGN_IN_TOP_MID, 0, 10);

    temp_label = lv_label_create(active_screen, NULL);
    // lv_obj_align(temp_label, screen_bg, LV_ALIGN_IN_TOP_MID, -100, 50);
    static lv_style_t temp_style;
    lv_style_init(&temp_style);
    lv_style_set_text_font(&temp_style, LV_STATE_DEFAULT, LV_THEME_DEFAULT_FONT_TITLE);
    lv_style_set_text_color(&temp_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_add_style(temp_label, LV_OBJ_PART_MAIN, &temp_style);
    lv_label_set_text(temp_label, "INITIALIZING . . .");
    lv_label_set_align(temp_label, LV_LABEL_ALIGN_CENTER);
    lv_obj_align(temp_label, screen_bg, LV_ALIGN_CENTER, 0, 40);
    
    // Create object/style/label for aws threshold
    // Create style first
    static lv_style_t awsObj_style;
    lv_style_init(&awsObj_style);
    lv_style_set_bg_color(&awsObj_style, LV_STATE_DEFAULT, lv_color_make(253, 153, 0)); //Default color

    static lv_style_t awsLab_style;
    lv_style_init(&awsLab_style);
    lv_style_set_text_font(&awsLab_style, LV_STATE_DEFAULT, LV_THEME_DEFAULT_FONT_TITLE);
    lv_style_set_text_color(&awsLab_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);

    // Create object for threshold
    // lv_obj_t* awsPIR_obj;
    awsPIR_obj = lv_obj_create(active_screen, NULL);
    lv_obj_align(awsPIR_obj, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 110);
    lv_obj_set_size(awsPIR_obj, 130, 40); // 300/2 = 150, then padding 10 each side, so final size 130,
    lv_obj_set_click(awsPIR_obj, false);
    lv_obj_add_style(awsPIR_obj, LV_OBJ_PART_MAIN, &awsObj_style);

    awsPIR_lab = lv_label_create(awsPIR_obj, NULL);
    lv_obj_add_style(awsPIR_lab, LV_OBJ_PART_MAIN, &awsLab_style);
    lv_label_set_static_text(awsPIR_lab, "Detected: false");
    lv_obj_align(awsPIR_lab, awsPIR_obj, LV_ALIGN_IN_TOP_MID, 0, 10);

    // Create object for count
    // lv_obj_t* awsCount_obj;
    awsCount_obj = lv_obj_create(active_screen, NULL);
    lv_obj_align(awsCount_obj, NULL, LV_ALIGN_IN_TOP_LEFT, 170, 110); // X: 10+300/2+10
    lv_obj_set_size(awsCount_obj, 130, 40); // 300/2 = 150, then padding 10 each side, so final size 130,
    lv_obj_set_click(awsCount_obj, false);
    lv_obj_add_style(awsCount_obj, LV_OBJ_PART_MAIN, &awsObj_style);

    awsCount_lab = lv_label_create(awsCount_obj, NULL);
    lv_obj_add_style(awsCount_lab, LV_OBJ_PART_MAIN, &awsLab_style);
    lv_label_set_static_text(awsCount_lab, "Counter: 0");
    lv_obj_align(awsCount_lab, awsCount_obj, LV_ALIGN_IN_TOP_MID, 0, 10);

    // Create text area for message
    out_txtarea = lv_textarea_create(active_screen, NULL);
    // lv_obj_set_size(out_txtarea, 300, 80);
    lv_obj_set_size(out_txtarea, 300, 70);
    // lv_obj_align(out_txtarea, NULL, LV_ALIGN_IN_TOP_MID, 0, 150);
    lv_obj_align(out_txtarea, NULL, LV_ALIGN_IN_TOP_MID, 0, 160);
    lv_obj_set_click(out_txtarea, false);
    lv_textarea_set_max_length(out_txtarea, MAX_TEXTAREA_LENGTH);
    lv_textarea_set_text_sel(out_txtarea, false);
    lv_textarea_set_cursor_hidden(out_txtarea, true);
    lv_textarea_set_text(out_txtarea, "");

    xSemaphoreGive(xGuiSemaphore);

    xTaskCreatePinnedToCore(battery_task, "batteryTask", configMINIMAL_STACK_SIZE * 2, (void*) active_screen, 0, &power_handle, 1);
}