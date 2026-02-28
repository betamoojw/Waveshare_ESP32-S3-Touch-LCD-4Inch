# Smart Panel

## Open-Source Home Automation Control Panel
*ESP32-S3/P4 · LVGL · PlatformIO · Multi-Protocol*

## 📌 Overview
**Smart Panel** is an open-source wall-mounted home automation control system built on ESP32-S3, using LVGL for a modern embedded GUI and PlatformIO for development.

It integrates lighting, curtains, HVAC, scenes, energy monitoring, music, and security into a single unified touch interface — supporting professional building protocols (KNX / Modbus) and open smart home ecosystems (MQTT / Home Assistant).

## 🧠 Architecture Overview
```
+------------------------------------------------------------+
|                       LVGL GUI Layer                       |
+------------------------------------------------------------+
|                Application & Scene Engine                  |
|  Lighting | HVAC | Curtain | Energy | Security | Ohters    |
+------------------------------------------------------------+
|                Protocol Abstraction Layer                  |
|  KNX | Modbus | MQTT | Home Assistant API                  |
+------------------------------------------------------------+
|                      Middleware Services                   |
|  Event Bus | Storage | OTA | Logging | Config | Web server |
+------------------------------------------------------------+
|                    Hardware Abstraction                    |
+------------------------------------------------------------+
|                      ESP32-S3/P4 MCU                       |
+------------------------------------------------------------+
```

## 🔧 Hardware Platform

### Core MCU
ESP32-S3
- Dual-core Xtensa LX7
- 2.4 GHz Wi-Fi
- BLE 5.0
- External PSRAM support
- Secure boot & flash encryption
- USB OTG

ESP32-P4-Core module
- ESP32-P4NRW32, 32MB Nor Flash
- SDIO interface protocol, extending Wi-Fi 6 / Bluetooth 5 (LE)
- External PSRAM support
- Secure boot & flash encryption
- USB OTG

Optional Interfaces
- Modbus (RTU via RS485, TCP via ethernet/WiFi)
- KNX IP over ethernet/WiFi or TP over TP-UART interfaces
- Ethernet (e.g. W5500)
- Audio codec (music source from internet)
- Capacitive touch display (480×480 / 720×720)
- MicroSD storage

### Off the shelf Hardware Platform
1. ✨ Waveshare ESP32-P4 Smart 86 Box (onboard Ethernet port + RS485 + 2-ch relay + 720×720), https://www.waveshare.com/esp32-p4-wifi6-touch-lcd-4b.htm
2. esp32-4848S040CIY1 (480*480 IPS, ESP32-S3-N16R8, with 1 relay), https://www.aliexpress.com/item/1005006302276974.html
3. esp32-4848S040CIY1 (480*480 IPS, ESP32-S3-N16R8, with 3 relays), https://www.aliexpress.com/item/1005006302276974.html
4. Waveshare ESP32-S3-Touch-LCD 4Inch, https://www.waveshare.com/esp32-s3-touch-lcd-4.htm


## 🎨 GUI Framework
LVGL
- Lightweight embedded graphics
- Animation & theme support
- Multi-language ready
- Touch optimized
- Hardware acceleration support

## 🌐 Supported Protocols
| Protocol       | Mode       | Purpose                          |
| -------------- | ---------- | -------------------------------- |
| KNX            | TP/IP      | Professional building automation |
| Modbus         | RTU/TCP    | HVAC / Energy meters             |
| MQTT           | TCP/IP     | IoT messaging                    |
| Home Assistant | API / MQTT | Smart home integration           |

*All protocols are implemented through a unified abstraction interface.*


## ✨ Features

### 💡 Lighting Control

![Screenshot of light control](assets/light_control.png)

- On / Off
- Dimming (0–100%)
- RGB & Tunable White
- Group control
- Real-time state sync
- KNX group address binding via web server config if KNX is supported
- Modbus objects binding via web server  config if modbus is supported

### 🪟 Curtain Control

![Screenshot of curtain control](assets/curtain_control.png)

- Open / Close / Stop
- Percentage positioning
- Scene integration
- Status feedback

### 🌡 HVAC Control

![Screenshot of HVAC control](assets/hvac_control.png)

- Mode: Cool / Heat / Auto / Fan
- Temperature setting
- Fan speed
- Real-time sensor feedback
- Modbus / KNX integration if supported


### ⚡ Energy Monitoring

![Screenshot of energy monitoring](assets/energy_monitoring.png)

- Real-time power
- Daily / Weekly / Monthly reports
- Historical charts
- Data export


### 🎵 Music Contro

![Screenshot of music control](assets/music_control.png)

- Play / Pause / Next / Previous
- Volume control
- Source selection
- Media entity sync with Home Assistant

### 🔐 Security

![Screenshot of security](assets/security.png)

- Arm / Disarm
- Sensor status display
- Motion alerts
- PIN authentication
- Secure remote sync


### 🔄 OTA Update

![Screenshot of OTA](assets/ota.png)

- OTA via internet over WiFi/Ethernet 
- Dual partition fallback
- Signed firmware
- Web update portal


### 🔐 Security Features

- TLS encryption (MQTT)
- Secure Boot
- Flash encryption
- Role-based UI access
- Local PIN protection


## 🗂 Repository Structure
*todo*

## 🚀 Getting Started with VSCode
### Install PlatformIO
```
pip install platformio
```
### Clone Repository
```
git clone https://github.com/your-org/smart-panel.git
cd smart-panel
```
### Build & Flash
```
pio run
pio run --target upload
```
### Configure
- Connect to device Wi-Fi AP
- Open configuration portal
- Configure:
  - Internet connectivity(e.g. ethernet, WiFi)
  - MQTT
  - KNX
  - Modbus
  - Home Assistant


## 🧩 Extending the Project
### Add a New Protocol
1.  Implement IProtocol interface
2. Register in Protocol Manager
3. Map to UI data model

### Add a New UI Module
1. Create LVGL screen
2. Register in screen manager
3. Bind to event bus


## 🛣 Roadmap

- Multiple protocols support
- Gateway mode
- AI agent integration
- Cloud dashboard
- AI-based energy optimization


## 📜 License
- Firmware: MIT / Apache 2.0
- Hardware: CERN-OHL
- Documentation: CC-BY-SA


## 🤝 Contributing
We welcome contributions!

  1. Fork the repo
  2. Create feature branch
  3. Submit pull request
  4. Follow coding guidelines in /docs/contribution.md

## ⭐ Vision
Smart Panel bridges professional building automation (KNX / Modbus / Other protocols) with open smart home ecosystems (MQTT / Home Assistant) — creating a powerful, flexible, and developer-friendly platform.




## Read more at
1. https://github.com/nishad2m8/Display-Panel-CYD/tree/master/02-Coffee-vending
2. https://github.com/rzeldent/esp32-smartdisplay
3. https://github.com/rzeldent/esp32-smartdisplay-demo