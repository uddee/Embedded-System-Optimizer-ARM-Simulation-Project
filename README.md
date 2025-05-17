# Embedded-System-Optimizer-ARM-Simulation-Project

This project demonstrates performance profiling and interrupt optimization on an ARM Cortex-M4-based microcontroller using **Keil uVision5** and **CMSIS** libraries.

It simulates:
- GPIO interrupt using a button (PA0)
- LED toggle (PD12)
- Cycle count profiling inside the ISR using the **DWT Cycle Counter**

---

## 🛠 Features

- ✅ ARM Cortex-M4 (STM32F407) interrupt handling
- ✅ Real-time cycle count measurement via DWT
- ✅ Low-level CMSIS (register-level) programming
- ✅ Optimized ISR for minimum latency
- ✅ Low-power mode usage (`__WFI()`)

---

## 📂 Project Structure

EmbeddedSystemOptimizer/
│
├── main.c # Core application
├── startup_stm32f4xx.s # Startup file (Keil)
├── system_stm32f4xx.c # System init (clock config)
├── README.md # You're here
├── .uvprojx # Keil project config
└── .uvoptx # Keil debug/session settings

yaml
Copy
Edit

---

## 🔧 Requirements

- [Keil MDK-ARM](https://www.keil.com/mdk5/) (uVision5)
- STM32F4 device pack installed
- ARM Cortex-M4-based MCU (e.g., STM32F407)
- Basic hardware: Push-button on PA0 and LED on PD12 (optional for simulation)

---

## 📈 How It Works

1. **Interrupt Trigger**:
    - User presses a button (PA0)
    - EXTI0 interrupt is fired

2. **ISR Execution**:
    - DWT Cycle Counter starts at entry
    - LED on PD12 toggled
    - DWT stops at exit
    - `cycles_taken` stores the total cycle count for profiling

3. **Power Optimization**:
    - CPU enters low-power state via `__WFI()` in the main loop

---

## 📊 Output Example

Watch `cycles_taken` in the **Keil Debugger Watch Window** after pressing the button:

```txt
cycles_taken = 47

Debugging Tips
Use Cycle Counter (DWT->CYCCNT) in Keil debugger

Breakpoints can interfere with exact cycle counts — use them sparingly

Profile across multiple button presses to average runtime

📚 References
ARM Cortex-M4 Technical Reference Manual

STM32F4 Reference Manual (RM0090)

CMSIS documentation from ARM

Keil DWT cycle counter article

