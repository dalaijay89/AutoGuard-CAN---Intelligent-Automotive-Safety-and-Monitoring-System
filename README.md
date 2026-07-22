# 🚗 AutoGuard CAN: Intelligent Automotive Safety & Monitoring System

> 🚀 A CAN (Controller Area Network) based embedded system for real-time vehicle monitoring, fuel level tracking, indicator control, and accident detection using multiple LPC2129 nodes.

---

## 📖 Overview

**AutoGuard CAN** is an intelligent automotive safety and monitoring system designed using the **Controller Area Network (CAN)** protocol. The project enables communication between multiple embedded nodes to monitor important vehicle parameters and improve vehicle safety.

The system continuously monitors:

- 🚨 Accident Detection (Accelerometer)
- ⛽ Fuel Level Monitoring
- 💡 Indicator Control
- 📊 Real-Time Data Display
- 🔄 CAN-based Inter-node Communication

When an accident is detected, the system analyzes sensor data and immediately updates the deployment status, allowing quick response and monitoring.

---

# ✨ Features

✅ Real-time Vehicle Monitoring

✅ CAN Bus Communication

✅ Fuel Level Measurement

✅ Accident Detection using Accelerometer

✅ Indicator Control through CAN

✅ LCD Status Display

✅ External Interrupt Handling

✅ Multi-node Embedded Architecture

---

# 🏗️ System Architecture

The project consists of **three CAN nodes**.

### 🔹 Main Node

- Reads Accelerometer values
- Detects accidents
- Displays sensor data on LCD
- Receives fuel level information
- Sends CAN messages to other nodes
- Controls deployment status

### 🔹 Fuel Node

- Reads fuel sensor through ADC
- Sends fuel percentage to Main Node via CAN

### 🔹 Indicator Node

- Receives CAN messages
- Controls LED indicators
- Displays accident indication

---

# 🧩 Block Diagram

```
                +----------------------+
                |      Main Node       |
                |----------------------|
                | LPC2129              |
                | LCD                  |
                | Accelerometer        |
                | CAN Controller       |
                +----------+-----------+
                           |
===================== CAN BUS =====================
         |                               |
         |                               |
+--------+---------+         +-----------+--------+
| Indicator Node   |         | Fuel Node          |
| LPC2129          |         | LPC2129            |
| LEDs             |         | Fuel Sensor        |
| CAN Controller   |         | ADC               |
+------------------+         +-------------------+
```

---

# ⚙️ Hardware Requirements

- 🖥️ LPC2129 Microcontroller
- 🔌 MCP2551 CAN Transceiver
- 📟 16x2 LCD
- 💡 LEDs
- 📈 MMA7660 Accelerometer
- ⛽ Fuel Sensor
- 🎛️ Switches
- 🔄 USB to UART Converter

---

# 💻 Software Requirements

- Embedded C
- Keil uVision
- Flash Magic

---

# 📂 Project Structure

```
AutoGuard-CAN/
│
├── Main_Node/
│   ├── main.c
│   ├── can.c
│   ├── lcd.c
│   └── interrupt.c
│
├── Fuel_Node/
│   ├── fuel.c
│   └── adc.c
│
├── Indicator_Node/
│   ├── indicator.c
│   └── led.c
│
│
└── README.md
```

---

# 🔄 Working Principle

### 🚗 Main Node

- Reads accelerometer continuously.
- Detects sudden acceleration.
- Checks accident threshold.
- Displays values on LCD.
- Receives fuel data from Fuel Node.
- Sends CAN messages to Indicator Node.

### ⛽ Fuel Node

- Reads fuel sensor.
- Converts analog value using ADC.
- Sends fuel percentage over CAN.

### 💡 Indicator Node

- Waits for CAN message.
- Controls LEDs.
- Displays accident indication.

---

# 🚀 Implementation Steps

1️⃣ Configure LPC2129 project

2️⃣ Initialize GPIO

3️⃣ Configure ADC

4️⃣ Configure LCD

5️⃣ Configure CAN Controller

6️⃣ Configure External Interrupts

7️⃣ Read Fuel Sensor

8️⃣ Read Accelerometer

9️⃣ Transmit CAN Frames

🔟 Receive CAN Frames

1️⃣1️⃣ Display Output on LCD

1️⃣2️⃣ Test complete communication

---

# 📷 Output

The system displays:

- 📊 Fuel Percentage
- 🚨 Accident Status
- 💡 Indicator Status
- 📡 CAN Communication Status

---

# 🎯 Applications

- 🚗 Smart Vehicles
- 🚘 Automotive Safety Systems
- 🚓 Fleet Monitoring
- 🚙 Intelligent Transportation
- 🚌 Vehicle Health Monitoring
- 🛡️ Accident Alert Systems

---

# 🌟 Future Enhancements

- 📍 GPS Integration
- 📶 GSM Accident Alert
- ☁️ IoT Cloud Monitoring
- 📱 Mobile Application
- 📡 Wireless CAN Monitoring
- 🤖 AI-based Accident Prediction

---

# 🛠️ Technologies Used

- Embedded C
- LPC2129
- CAN Protocol
- MCP2551
- ADC
- GPIO
- LCD Interface
- Interrupt Programming

---

# 📚 Learning Outcomes

This project provides hands-on experience in:

- Embedded C Programming
- CAN Protocol
- ARM7 LPC2129
- ADC Programming
- Interrupt Handling
- Embedded Communication
- Sensor Interfacing
