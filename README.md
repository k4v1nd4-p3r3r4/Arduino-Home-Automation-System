# 🏠 Arduino Home Automation System

An Arduino Uno-based Home Automation System that integrates **motion detection**, **gas leakage detection**, **temperature monitoring using a thermistor**, and **water level control using a 3-pin ultrasonic sensor**.

## 📦 Features

- 🔧 **Motion Detection** (PIR Sensor)
  - Turns on a **buzzer** and **bulb** when motion is detected.
  
- 🛑 **Gas Leak Detection** (MQ2 or MQ135)
  - Sounds **buzzer** when gas concentration exceeds a threshold.
  
- 🌡️ **Temperature Monitoring** (Thermistor + Voltage Divider)
  - Sounds **buzzer** when temperature exceeds a defined limit (e.g., 35°C).

- 💧 **Water Level Monitoring** (3-pin Ultrasonic Sensor)
  - Activates **water motor** when the water level is low.

---

## 🔌 Components Used

| Component              | Description                        |
|------------------------|------------------------------------|
| Arduino Uno            | Microcontroller                    |
| PIR Motion Sensor      | Motion detection                   |
| Buzzer                 | Alert output                       |
| Relay + Bulb           | Visual alert for motion detection  |
| MQ2/MQ135 Gas Sensor   | Detects harmful gases              |
| 10k Thermistor         | Measures temperature               |
| 10k Resistor           | Used in thermistor voltage divider|
| 3-Pin Ultrasonic Sensor| Measures water level               |
| Water Pump + Relay     | Auto motor control                 |
| Breadboard + Wires     | Circuit assembly                   |

---

## ⚙️ Circuit Summary

- **PIR Sensor** → Digital Pin `2`
- **Buzzer** → Digital Pin `3`
- **Bulb (via relay)** → Digital Pin `4`
- **Gas Sensor** → Analog Pin `A0`
- **Thermistor** → Analog Pin `A1` (with 10k resistor voltage divider)
- **Ultrasonic (Trig+Echo)** → Digital Pin `6`
- **Water Motor (via relay)** → Digital Pin `8`

---

## 🧠 How It Works

1. **Motion Detected?**
   - ✅ Yes → Turn on buzzer + bulb for alert
   - ❌ No → Turn off alert

2. **Gas Level High?**
   - ✅ Yes → Sound buzzer

3. **Temperature High?**
   - ✅ Yes → Sound buzzer

4. **Water Level Low?**
   - ✅ Yes → Turn on motor
   - ❌ No → Turn off motor

---
