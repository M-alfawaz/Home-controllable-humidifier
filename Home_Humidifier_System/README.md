# Home Controllable Humidifier 🌫️

## Project Overview
An **Arduino-based humidifier controller** that monitors temperature and humidity using a **DHT11** and an analog humidity sensor.  
When the humidity falls below a desired threshold, the system turns the humidifier ON via a **relay** for 30 seconds, then rechecks humidity.  
A **16x2 LCD** displays live readings.

## Components Used
- Arduino Uno R3
- 16x2 LCD Display
- Blue LED + 220Ω Resistor
- Two 10k Potentiometers
- Relay module
- Water Level Detection Sensor
- DHT11 Temperature & Humidity Sensor
- Breadboard & Jumper wires

## Features
- Real-time temperature & humidity monitoring
- Automatic humidifier control (30s cycle)
- LCD feedback for sensor values and status

## How to Run
1. Open `src/humidifier.ino` in Arduino IDE.
2. Install libraries: `LiquidCrystal`, `SimpleDHT`.
3. Wire the LCD, DHT11, water-level sensor, and relay as in your circuit.
4. Upload and test.

## Documentation
See [`docs/Home_Humidifier_System.pdf`](docs/Home_Humidifier_System.pdf) for the full report.
