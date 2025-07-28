# REAL_TIME_MONITORING_SYSTEM_AC_MACHINES

# Real-Time Monitoring of Single Phase Induction Motor Parameters Using ESP32

This project demonstrates a real-time monitoring system for a single-phase induction motor using an ESP32 microcontroller. It focuses on improving operational safety and efficiency by continuously tracking **voltage**, **current**, and **speed (RPM)** using sensors and triggering alerts when critical thresholds are exceeded.

## 📌 Features

- AC voltage measurement using ZMPT101B sensor
- Current measurement using ACS712 sensor (5A/20A/30A)
- Speed detection using an Inductive Proximity Sensor
- Real-time alert system using an LED
- Serial monitoring via Arduino IDE
- Scalable and cost-effective design suitable for domestic and industrial applications

---

## 🛠️ Components Required

### Sensors
- **ZMPT101B** – AC voltage measurement  
- **ACS712 (5A/20A/30A)** – Current measurement  
- **Inductive Proximity Sensor** – RPM detection  

### Microcontroller
- **ESP32-WROOM** (Wi-Fi + Bluetooth)

### Power Supply
- **5V** for sensors and ESP32  
- **12V** for proximity sensor  

### Other Components
- Resistors (27kΩ and 10kΩ for voltage divider)  
- Breadboard, Jumper Wires, LED  
- Optional: PCB for permanent setup  
- Arduino IDE, Heat Shrink Tubes, Soldering Setup

---

## 📋 Implementation Overview

1. Sensors are connected to the ESP32 on analog pins (GPIO 34 and 35).
2. ESP32 reads the voltage and current data and calculates RMS and actual values.
3. RPM is detected via a proximity sensor counting pulses.
4. If measured parameters exceed set thresholds (e.g., 240V or 6A), an LED is triggered to blink as an alert.
5. Data is printed via serial monitor for observation and logging.

---

## 📷 Experimental Setup


System setup on a breadboard (optionally on PCB) including:
- ESP32
- Voltage/Current sensors
- RPM sensor
- LED for alerts

---

## 💡 Code Overview

Main features in the code (`AC_MACHINES_PROJECT.ino`):
- `get_voltage()` – Calculates RMS voltage using ZMPT101B  
- `get_current()` – Reads current using ACS712  
- Blinks LED if thresholds are exceeded  
- Serial prints real-time values

```cpp
if ((volt_rms1 >= voltage_threshold) || (current >= current_threshold)) {
    digitalWrite(LED_Pin, HIGH); // Alert
} else {
    digitalWrite(LED_Pin, LOW);
}


## 🔗 Future Work
Wi-Fi/Bluetooth-based dashboard monitoring

Data logging to cloud/server

Integration with mobile apps for remote alerts

Enhanced PCB-based deployment
