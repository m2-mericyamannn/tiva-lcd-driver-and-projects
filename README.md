# Tiva C Embedded Systems Projects

This repository contains a structured set of **embedded systems projects** developed using the **Tiva C (TM4C123)** microcontroller platform.  
Each project builds on the previous one, gradually introducing new peripherals, software abstractions, and system-level concepts.

---

## 📁 Project Overview

```
Tiva-C-Projects/
│
├── 01_16x2_LCD_Driver_Development/
├── 02_LCD_Clock_App/
├── 03_LCD_ADC_Display/
└── 04_LCD_ADC_UART_Project/
```

Each folder is a self-contained project with its own source files and README documentation.

---

## 🔹 Project 01 – 16x2 LCD Driver Development

**Goal:**  
Develop a low-level driver to control a 16x2 HD44780-compatible LCD using GPIO in 4-bit mode.

**Key Features:**
- Direct GPIO control
- 4-bit LCD communication
- Cursor positioning
- Character printing
- Clean modular LCD driver

**Main Concepts:**
- GPIO configuration
- Timing control using delays
- LCD command & data handling

📁 Folder: `01_16x2_LCD_Driver_Development`

---

## 🔹 Project 02 – LCD Clock Application

**Goal:**  
Extend the LCD driver by adding a **software-based clock** using Timer0 interrupts.

**Key Features:**
- 1-second periodic timer interrupt
- Software timekeeping (HH:MM:SS)
- LCD update synchronized with timer
- Clean ISR-to-main communication

**Main Concepts:**
- Timer0 configuration
- Interrupt-driven design
- Separation of ISR logic and display logic

📁 Folder: `02_LCD_Clock_App`

---

## 🔹 Project 03 – LCD + ADC Voltage Display

**Goal:**  
Introduce **ADC functionality** to read and display analog voltage values on the LCD.

**Key Features:**
- ADC0 (Channel 9 – PE4) usage
- 12-bit ADC conversion
- Voltage calculation and formatting
- Real-time voltage display on LCD

**Main Concepts:**
- ADC configuration
- Analog-to-digital conversion
- Data formatting for display

📁 Folder: `03_LCD_ADC_Display`

---

## 🔹 Project 04 – LCD + ADC + UART Integration

**Goal:**  
Build a complete embedded system combining **LCD, ADC, Timer, and UART communication**.

**Key Features:**
- UART communication with PC
- Command-based interaction
- Real-time ADC and clock reporting
- Button-triggered events
- Modular architecture

**Main Concepts:**
- UART RX/TX handling
- Command parsing
- Event-driven programming
- Scalable system design

📁 Folder: `04_LCD_ADC_UART_Project`

---

## 🧩 Project Structure Philosophy

Each project:
- Builds on the previous one
- Reuses and extends existing modules
- Follows modular and readable code design
- Is suitable for educational and portfolio purposes

---

## 🧠 Target Skills Covered

- Embedded C programming  
- GPIO and peripheral configuration  
- Interrupt handling  
- ADC and UART communication  
- Modular firmware architecture  
- Real-time embedded concepts  

---

## 🛠 Development Environment

- **MCU:** TM4C123 (Tiva C Series)
- **IDE:** Code Composer Studio 
- **Library:** TivaWare DriverLib
- **Language:** C

---

## 📌 Notes

- All projects are tested incrementally.
- Each folder contains its own README with detailed explanations.
- Code is structured for readability and extensibility.

---


📎 **This repository is designed as a progressive learning path for embedded systems development using Tiva C.**
