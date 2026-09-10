# AirPaddle: Low-Latency Motion-Controlled Web Game System

AirPaddle bridges physical motion with web-based gaming using an ESP32 microcontroller, an MPU-6050 accelerometer/gyroscope, and bi-directional WebSockets. By streaming real-time sensor data over Wi-Fi, hand gestures on a custom breadboard circuit control an in-browser Pong game with near-zero latency, complete with hardware-driven audio feedback.

---

## 📽️ Project Demo

![AirPaddle Demo](pingponggame.mp4)

---

## ⚡ System Architecture
[ MPU-6050 IMU ] ---> (I2C) ---> [ ESP32 Microcontroller ]
|
(WebSockets/Wi-Fi)
v
[ Web Browser Engine ]
|
[ Piezo Buzzer ] <--- (PWM Signal)
---

## 🛠️ Features & Engineering Highlights

* **Real-Time Gesture Tracking:** Computes pitch/roll angles using 6-axis IMU data to translate physical tilts into precise paddle movement.
* **Low-Latency WebSockets:** Event-driven TCP connection ensures sub-millisecond data transfer between ESP32 and the frontend.
* **Hardware Audio Feedback:** Onboard piezo speaker generates dynamic tone frequencies for ball bounces and scoring.
* **Cross-Platform Compatibility:** Runs directly in any web browser without third-party desktop drivers.

---

## 📦 Components Required

* ESP32 NodeMCU Development Board
* MPU-6050 Accelerometer / Gyroscope
* Piezo Passive Buzzer
* Breadboard & Jumper Wires
* Micro-USB Data Cable

---

## 🔌 Hardware Connections

| Component Pin | ESP32 Pin | Function |
| :--- | :--- | :--- |
| **MPU-6050 VCC** | 3.3V | Power Supply |
| **MPU-6050 GND** | GND | Ground |
| **MPU-6050 SDA** | GPIO 21 | I2C Data Line |
| **MPU-6050 SCL** | GPIO 22 | I2C Clock Line |
| **Buzzer (+)** | GPIO 18 | PWM Audio Output |
| **Buzzer (-)** | GND | Ground |

---

## 🚀 Quickstart & Setup

### 1. ESP32 Firmware
1. Open `firmware/esp32_pong.ino` in Arduino IDE.
2. Install dependencies via Library Manager:
   * `Adafruit MPU6050`
   * `WebSockets` by Markus Sattler
3. Input your Wi-Fi credentials in the sketch:
   ```cpp
   const char* ssid = "YOUR_WIFI_NAME";
   const char* password = "YOUR_WIFI_PASSWORD";
   ## 🛠️ Tech Stack

![ESP32](https://img.shields.io/badge/Hardware-ESP32-red?style=for-the-badge&logo=espressif)
![C++](https://img.shields.io/badge/Language-C++-blue?style=for-the-badge&logo=cplusplus)
![WebSockets](https://img.shields.io/badge/Protocol-WebSockets-orange?style=for-the-badge)
![JavaScript](https://img.shields.io/badge/Frontend-JavaScript-yellow?style=for-the-badge&logo=javascript)
![HTML5](https://img.shields.io/badge/UI-HTML5-E34F26?style=for-the-badge&logo=html5)
