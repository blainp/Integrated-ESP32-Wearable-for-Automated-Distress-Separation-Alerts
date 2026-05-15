# Wearable System For Automated Separation Alerts
This project features a wearable ESP32-C3 based distress beacon designed to provide a redundant safety layer by monitoring a persistent Wi-Fi handshake with a user’s smartphone. By leveraging iOS Shortcuts to detect an immediate state-change upon connection loss, the system triggers an automated emergency alert to pre-defined contacts if this device and a user's phone are forcibly separated. The implementation prioritizes an inconspicuous form factor and optimized power management, utilizing a recycled lithium-ion cell to maintain a low-power discovery service for extended field use.

---

## Project Overview

<p align="center">

  <img width="350" src="https://github.com/user-attachments/assets/f7e0c13f-399c-461b-8a2c-9a949f581fa2" alt="System Diagram">

  <img width="450" margin-top="500px" alt="3dFile" src="https://github.com/user-attachments/assets/fe27d63d-b476-471a-a850-adea5ee02db3" />

</p>


### Design Philosophy & Threat Model

This device was developed to address a critical oversight in the standard use of technology for personal safety. 

> If a vulnerable individual who was travelling in isolation and did not have access to an immediate support network were to be assaulted or abducted, the first thing most MCF assailants would do is forcibly discard their smartphone or render them incapable of utilizing it to call for help.

**By implementing a redundant tether** between the wearer's iPhone and this device, which would be hidden on the wearer's body, an alert could be sent regardless of whether or not the user has access to their device, or is physically capable of utilizing their device to call for help. 

**Unlike consumer alternatives:** While platforms like the Apple Watch or AirTag offer location tracking, they lack native "dead man's switch" functionality and are increasingly limited by anti-stalking features that alert unauthorized parties to their presence. By utilizing the iOS Shortcuts ecosystem, this project implements a custom hardware-to-software handshake that triggers automated distress signals based on network state changes, bypassing the functional limitations of consumer-grade trackers.

### Hardware & Power Architecture

This system employs an ESP32-C3, a small lithium-ion battery (taken from an old vape), and an inexpensive USB-C Li-Ion battery management and charging board. 

**Operational States:** On startup, the ESP32 runs a Wi-Fi discovery program at a low polling rate until a connection with a device is established. Once this connection is established, the ESP32 enters a very low-power Wi-Fi configuration, simply powering up intermittently to check its connection status and communicate with the user's phone. 

Even though this system utilizes a relatively small 600mAh Li-Ion battery, this setup can achieve up to 18+ hrs of run-time on a single charge.  

### Software Integration & Mobile Data Logic

Due to this system utilizing a combination of a simple Wi-Fi connection and the "Shortcuts" app, it can effectively function with any modern iPhone. 

**User Configuration:** To set it up, you simply connect to the ESP32's Wi-Fi network, open the "Shortcuts" app, and create a routine for when your phone disconnects from the network. You can customize the way your device responds to disconnection and have it send any message you please, such as "Phone disconnected from tracker for 5 min, call me to make sure I'm safe". These messages can be instructed to send to any of your contacts, and any action that the Shortcuts app could take, such as sharing current location, could also be programmed to run in this "routine". 

**Network Behavior:** Although the user is connecting to the ESP32's Wi-Fi network, the internet connection is not impaired as long as they have mobile data, as iPhones will prompt the user to "Use without internet" whenever connected to a network that does not supply an internet connection. This means a user can leave their iPhone connected to the ESP32 network while using mobile data without impairing their internet connection or lowering the accuracy of their device's GPS tracking.

---

## Features

### Proximity-Based Handshake
- Hosts a localized low-power Wi-Fi network directly from the wearable hardware.
- Maintains a constant, lightweight verification loop with the paired smartphone.

### iOS Automation Integration
- Leverages native iOS Automation triggers upon network separation.
- Completely customizable emergency routine sequences (SMS alerts, GPS location dispatch, background audio recording, etc.).

### Stealth & Hardware Optimization
- Compact, hidden form factor optimized for discrete on-body concealment.
- Deep sleep and low polling-rate logic tailored to maximize battery performance.

---

---

## Repository Structure

```text
/Diagrams
    Hardware schematic and system wiring diagrams

/Documentation
    Design reports, system architecture, and presentation files

/Firmware
    C++/Arduino source code for the ESP32-C3 power-saving Wi-Fi loop

/3D Models
    Enclosure designs and Fusion 360 models for wearable housing
```

---

## Bill of Materials (BOM)

| Component | Description | Function |
| :--- | :--- | :--- |
| Microcontroller | ESP32-C3 Development Board | Hosts local Wi-Fi beacon and manages sleep states |
| Power Source | Recycled 600mAh Li-Ion Cell (Vape Hardware) | Provides lightweight power to the standalone system |
| Charge Controller | USB-C Li-Ion Charging Board (TP4056 or similar) | Manages battery safety and power regulation |
| Toggle Switch | Hardware power switch | Turns the beacon on/off manually |

<p align="center">
<img width="1000" alt="image" src="https://github.com/user-attachments/assets/245cce53-bb9a-4866-85ff-58a84818fe8b" />
</p>

---

## Technical Specifications & Power Profile

The tracking loop relies heavily on optimizing the ESP32-C3's internal Wi-Fi modem states to prevent rapid battery depletion while retaining quick reconnection responses.

### Performance Profile

- **Target Run-Time:** `18+ Hours`
  - Projected continuous operational window using a standard repurposed 600mAh cell.
- **Network Handshake Check Interval:** `Low-Frequency Duty Cycle`
  - Designed to cycle the radio power up and down dynamically once a smartphone handshake is secured.

---

## Installation & Setup

### 1. Hardware Firmware Flash
* Open the source files inside the `/Firmware` directory using the Arduino IDE or VS Code (PlatformIO).
* Install the required ESP32 core boards package.
* Connect your ESP32-C3 via USB-C and flash the codebase.

### 2. iOS Shortcut Configuration
* Power on the flashed beacon device.
* Navigate to your iPhone's **Wi-Fi Settings** and connect to the beacon's network broadcast. Select **"Use without internet"** when prompted by iOS.
* Open the **Shortcuts** app on iOS and navigate to the **Automation** tab.
* Create a **New Personal Automation** selecting **Wi-Fi** as the trigger.
* Choose **Network Name (Your Beacon SSID)** and set the trigger condition to **"Disconnects"**.
* Add actions to your routine (e.g., *Send Message [Custom Distress Text] to [Emergency Contacts]* / *Get Current Location*).

---

## Known Constraints & Future Recommendations

### Antenna Shielding
Depending on enclosure placement and on-body positioning, human tissue attenuation can cause premature drops in Wi-Fi signal. Fine-tuning the transmission power (Tx Power) settings in firmware is recommended.

### Battery Optimization
While the system operates on a low-frequency polling rate, migrating the firmware entirely to native ESP-IDF Espressif frameworks (rather than the Arduino layer) could further shave off milliamp-hours during deep sleep cycles.
