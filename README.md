# 🛠️ Workshop Ambient Light (C++ OOP Approach)

This project is a hardware-controlled ambient light for my workshop.

## 🚀 Why this project is unique
Instead of using standard Arduino delay-based logic, I implemented this project using **Industrial Programming Patterns**. I wrote custom classes to replicate PLC (Programmable Logic Controller) behaviors, making the code robust, reusable, and easy to debug.

### Key Engineering Features:
* **Custom PLC-Style Classes:** I developed my own classes for **Edge Detection** (`EdgePosNeg`) and **On-Delay Timers** (`Ton`), mirroring standard industrial logic (IEC 61131-3).
* **Robust State Machine:** The entire light control is managed by a structured state machine, ensuring predictable transitions between standby, active, and adjustment modes.
* **Non-Blocking Logic:** By using my custom timer classes, the system remains fully responsive to button presses at all times.
* **Hardware Interfacing:** Designed for physical interaction with buttons to adjust RGB values and power states, including long-press detection for brightness ramping.

## 🛠️ Features
* **Manual RGB Tuning:** Each color channel (Red, Green, Blue) can be adjusted individually via dedicated buttons.
* **Smart Power Toggle:** A master power button with integrated edge detection to prevent accidental multi-triggers.
* **Persistent Logic:** The system uses a structured approach to manage LED states, allowing for smooth value increments and wrap-around logic.

## 📁 Project Structure & OOP Design
The project is split into modular components, showing a clean separation of concerns:
* `src/main.cpp`: Manages the state machine and hardware I/O.
* `lib/Ton/`: A custom class for **On-Delay Timers**, allowing for clean timing logic without `delay()`.
* `lib/EdgePosNeg/`: A utility class for detecting rising and falling edges of digital signals.
* `src/config/`: Centralized configuration for pins and system constants.

## 🔧 Technical Stack
* **Microcontroller:** ESP32-C3 / ESP8266 (D1 Mini)
* **Framework:** Arduino / PlatformIO
* **Language:** C++ (Object-Oriented)
* **Hardware:** RGB LED Strip (Analog/PWM), Capacitive Touch Buttons

---
*This project serves as a bridge between classic industrial automation logic and modern embedded C++ development.*
