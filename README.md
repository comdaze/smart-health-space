# M5Stack Core2 for Smart Healthy Space Code Repository
This is the accompanying code repository for microcontroller tutorials presented in the [Smart Healthy Space](http://smart-health-space.s3-website.cn-north-1.amazonaws.com.cn/) program using the [M5Stack Core2 for Smart Healthy Space](https://m5stack.com/products/m5stack-core2-esp32-iot-development-kit-for-aws-iot-edukit) reference Hardware.

Each of the folders in this repository contains a separate project as described below. All projects are compatible with [ESP-IDF v4.2](https://www.espressif.com/en/products/sdks/esp-idf) or [PlatformIO](https://platformio.org/) and runs on Espressif's port of the [FreeRTOS kernel](https://www.freertos.org/). Please ensure that your installation of PlatformIO is updated to the latest version of PlatformIO Core (5.1+) using the command `pio upgrade`. Follow the [AWS IoT EduKit — Getting Started](http://smart-health-space.s3-website.cn-north-1.amazonaws.com.cn/cn/getting-started.html) tutorial for instructions on how to setup your environment.

For Arduino, UIFlow, or MicroPython content and code, please view the official [M5Stack Docs](https://docs.m5stack.com/#/).

## Included Projects
### Getting Started
This project is used in the [AWS IoT EduKit — Getting started](http://smart-health-space.s3-website.cn-north-1.amazonaws.com.cn/cn/getting-started.html) tutorial. It contains a port of [ESP RainMaker](https://rainmaker.espressif.com/). It is a quick end-to-end demonstration of a cloud connected smart home application. Please follow the tutorial for usage.

### Cloud Connected Blinky Hello World
This project is used in the [AWS IoT EduKit — Cloud Connected Blink](http://smart-health-space.s3-website.cn-north-1.amazonaws.com.cn/cn/blinky-hello-world.html) tutorial. It is a blinky LED demo that uses the on-board secure element for provisioning the device to AWS IoT and a FreeRTOS task to flash the on-board SK6812 LED bars. This example uses the [Espressif ported AWS IoT Device SDK for Embedded C](https://github.com/espressif/esp-aws-iot). Please follow the tutorial for usage.

### Smart Thermostat
This project is used in the [AWS IoT EduKit — Smart Thermostat](http://smart-health-space.s3-website.cn-north-1.amazonaws.com.cn/cn//smart-thermostat.html) tutorials. It is a demonstration that uses AWS IoT device shadow feature to provide an example of a smart thermostat and how to update device states through the device shadow feature. This example uses the [Espressif ported AWS IoT Device SDK for Embedded C](https://github.com/espressif/esp-aws-iot). Please follow the tutorial for usage.

### Healthy Spaces
This project is used in the [AWS IoT EduKit — Healthy Spaces](http://smart-health-space.s3-website.cn-north-1.amazonaws.com.cn/cn/Healthy-Spaces.html) tutorials. It is a demonstration that uses AWS IoT device shadow feature to provide an example of a smart thermostat and how to update device states through the device shadow feature. This example uses the [Espressif ported AWS IoT Device SDK for Embedded C](https://github.com/espressif/esp-aws-iot). Please follow the tutorial for usage.
