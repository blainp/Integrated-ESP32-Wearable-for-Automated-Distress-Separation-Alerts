# Wearable System For Automated Separation Alerts
This project features a wearable ESP32-C3 based distress beacon designed to provide a redundant safety layer by monitoring a persistent Wi-Fi handshake with a user’s smartphone. By leveraging iOS Shortcuts to detect an immediate state-change upon connection loss, the system triggers an automated emergency alert to pre-defined contacts if this device and a user's phone are forcibly separated. The implementation prioritizes an inconspicuous form factor and optimized power management, utilizing a recycled lithium-ion cell to maintain a low-power discovery service for extended field use.

---

## Project Overview
<p align="center">
  <img width="424" src="https://github.com/user-attachments/assets/93eb603f-b4d4-41a7-8a43-496c608952b2" alt="System Diagram">
  <img width="376" alt="Screenshot 2025-11-25 133809" src="https://github.com/user-attachments/assets/9647b5d3-e0db-49aa-8af9-4785628f9f04" />
</p>

This device was developed to address a critical oversight in the standard use of technology for personal safety. If a vulnerable individual who was travelling in isolation and did not have access to an immediate support network were to be assulted or abducted, the first thing most assailants would do is forcibly discard their smartphone or render them incapable of utilizing it to call for help. By implementing a redundant tether between the wearer's Iphone and this device, which would be hidden on the wearers body, an alert could be sent regardless of whether or not the user has access to their device, or is physically capable of utilizng their device to call for help. While platforms like the Apple Watch or AirTag offer location tracking, they lack native "dead man's switch" functionality and are increasingly limited by anti-stalking features that alert unauthorized parties to their presence. By utilizing the iOS Shortcuts ecosystem, this project implements a custom hardware-to-software handshake that triggers automated distress signals based on network state changes, bypassing the functional limitations of consumer-grade trackers.

This system employs an ESP32-C3, a small lithium ion battery (taken from an old vape), and an inexpensive USB-C Li-Ion batery management and charging board. On startup, the ESP32 runs a wifi discovery program at a very low polling-rate until connection with a device is established. Once this connection is established the ESP32 enters an even lower-power wifi mode, simply powering up to check and update the phone with its connection status. Even though my system utilized a relatively small 600mAh Li-Ion battery, this setup could theoretically achieve 18+ hrs of run-time on a single charge.  

Due to this system utilizing a combination of a simple WIFI connection and the "Shortcuts" app, it can effectively function with any modern Iphone. To set it up, you  simply connect to the ESP-32's WIFI network, open the "Shortcuts" app, and create a routine for when your phone disconnects from the network. You can customise the way your device responds to disconnection and have it send any message you please, such as "Phone disconnected from tracker for 5 min, call me to make sure I'm safe". These messages can be instructed to send to any of your contacts, and any action that the Shortcuts app could take, such as sharing current location, could also be programmed to run in this "routine". Although the user is connecting to the ESP-32's Wi-Fi network, internet connection is not impaired as long as they have mobile data, as Iphones will prompt the user to "Use without internet" whenever connected to a network that does not supply internet connection. This means a user can leave their Iphone connected to the ESP32 network while using mobile data without impairing internet connection or lowering the accuracy of their device's GPS tracking.

---

## Features

### Real-Time Monitoring
- Collects:
  - pH
  - Conductivity
  - Temperature
  - Turbidity

### Active Sampling System
- Uses a reservoir and pump system for consistent sample acquisition.


### Automated Alerting
- Sends Gmail email alerts when high-risk algal growth is detected.

### Predictive Analytics
- Uses supervised machine learning with surrogate thresholds to classify bloom risk into:
  - `algae_absent`
  - `algae_may_be_present`
  - `algae_present`
---

<p align="center">
<img width="376" alt="Snesor from front" src="https://github.com/user-attachments/assets/32d2aa59-d374-4e87-b092-e173afab4def" />
<img width="424" alt="betterclip2" src="https://github.com/user-attachments/assets/0319e15f-4df9-43eb-88ad-280d600d6044" />
</p>



## Repository Structure

```text
/Diagrams
    Wiring diagrams of system

/Documentation
    Formal IEEE report and presentation files

/Code
    Python scripts for machine learning model training and inference. Driver code for arduino

/3D Models
    Fusion Model of complete system
```

---

## Bill of Materials (BOM)

| Component | Description | Function |
|---|---|---|
| Microcontroller | IoT-enabled board (Arduino / ESP32) | Manages sensors and connectivity |
| pH Probe | Analog pH measurement probe | Monitors chemical spikes |
| Conductivity Sensor | Proxy indicator for nutrient levels | Detects high nutrient concentration (>300) |
| Turbidity Sensor | Measures water cloudiness | Low-cost surrogate for chlorophyll-a |
| Temperature Sensor | Waterproof DS18B20 probe | Tracks thermal growth conditions |
| Vacuum Pump | Micro 370 motor pump | Pulls water samples into the reservoir |
| Solenoid Valve | 12V valve | Responsible for draining the system |
| Boost Converter | XL6009 module | Converts 3.3V to 12V for solenoid operation |

---

## Machine Learning Performance

The system utilizes a surrogate threshold approach based on chlorophyll-a (Chla) guidelines from Health Canada using a **33 µg/L cutoff** for primary-contact water safety.

### Performance Metrics

- **Model Agreement Rate:** `84.74%`
  - Agreement between Random Forest and Gradient Boosting models on test data.

- **Primary Optimization Metric:** `Precision`
  - Designed to minimize false alarms while maintaining high sensitivity.

---

## Installation & Setup

### 1. Clone the Repository

```bash
git clone https://github.com/DorkyJuice/algalbloom_IOT.git
```

### 2. Initialize Submodules

```bash
git submodule update --init --recursive
```

### 3. Install Python Requirements

```bash
pip install -r requirements.txt
```

---

## Known Constraints & Future Recommendations

### Optimization
The current reservoir design is oversized for practical field deployment, leading to unnecessary energy consumption.

### Power Efficiency
The use of a 12V solenoid with a boost converter introduces substantial power losses. A native 3.3V solenoid is recommended for future revisions.

### Sensor Maintenance
The low-cost pH probe used in the prototype is highly sensitive and requires frequent recalibration and maintenance.

---

## References

This project was developed using guidance and threshold recommendations from:

- BC Ministry of Environment
- Health Canada

Additional references and citations are included in the Technical Report.
