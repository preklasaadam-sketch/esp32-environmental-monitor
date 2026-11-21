# Open ESP32 Environmental & System Monitor

An open-source hardware and software reference design for a modular IoT environmental monitoring system based on the ESP32 microcontroller.

## Overview
This repository contains the firmware, pinout specification, and hardware block diagrams for an open environmental sensor node. It measures ambient temperature, humidity, and atmospheric pressure, transmitting metrics over Wi-Fi using MQTT.

## Key Features
- **Microcontroller:** ESP32 (Wi-Fi & Bluetooth LE)
- **Sensors Supported:** BME280 / DHT22 via I2C/GPIO
- **Telemetry:** MQTT client with configurable update intervals
- **Power Management:** Deep-sleep functionality for battery-powered setups
- **Open License:** MIT License for unrestricted hardware & firmware prototyping

## Hardware Pinout
| Component | ESP32 Pin | Protocol |
| :--- | :--- | :--- |
| SDA (BME280) | GPIO 21 | I2C |
| SCL (BME280) | GPIO 22 | I2C |
| Status LED | GPIO 2 | GPIO Output |

## Getting Started
1. Open the project in **PlatformIO** or **Arduino IDE**.
2. Install the required libraries (`Adafruit BME280`, `PubSubClient`, `WiFi`).
3. Configure your Wi-Fi credentials and MQTT broker IP in `src/main.cpp`.
4. Compile and flash to your ESP32 board.

## License
Distributed under the MIT License. See `LICENSE` for more information.
