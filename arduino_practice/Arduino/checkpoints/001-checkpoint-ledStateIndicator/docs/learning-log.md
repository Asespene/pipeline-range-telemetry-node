# Checkpoint 01: Binary Device-State Indicator

**Date:** 2026-10-02  
**Target:** Arduino Uno / ATmega328P  
**Module:** Range Telemetry Node – Local Diagnostic Display

---

## 1. Overview
Implemented a physical diagnostic state indicator using 5 LEDs driven by GPIO output pins. Rather than running an unconstrained counter, the firmware extracts individual bits from a strongly-typed state enumeration (`enum class NodeState : uint8_t`) and projects the binary pattern onto physical LEDs via `bitRead()`.

---

## 2. Hardware Interface & Pin Mapping

Current flows from the GPIO output through a current-limiting resistor, through the LED (anode to cathode), to the common ground rail (`GND`).

| Pin | Bit Index | Weight | Role | State Association |
| :---: | :---: | :---: | :---: | :--- |
| `7`  | `0` | $2^0 = 1$ | LSB | Base State Bit 0 |
| `8`  | `1` | $2^1 = 2$ | Bit 1 | Base State Bit 1 |
| `9`  | `2` | $2^2 = 4$ | Bit 2 | Base State Bit 2 |
| `10` | `3` | $2^3 = 8$ | Bit 3 | Headroom / Warning Flag |
| `11` | `4` | $2^4 = 16$| MSB | Headroom / System Override |

---

## 3. State Truth Table

Base states are packed into bits 0–2 ($0\text{–}7$). Bits 3 and 4 remain reserved for future diagnostic flags.

| State Symbol | Value (Dec) | Value (Hex) | Binary Pattern (4 down to 0) | Physical LED State (Pin 11 $\rightarrow$ 7) |
| :--- | :---: | :---: | :---: | :--- |
| `STATE_BOOTING`       | `0` | `0x00` | `00000` | OFF, OFF, OFF, OFF, OFF |
| `STATE_READY`         | `1` | `0x01` | `00001` | OFF, OFF, OFF, OFF, ON  |
| `STATE_CLEAR`         | `2` | `0x02` | `00010` | OFF, OFF, OFF, ON, OFF  |
| `STATE_CAUTION`       | `3` | `0x03` | `00011` | OFF, OFF, OFF, ON, ON   |
| `STATE_OBJECT_NEAR`   | `4` | `0x04` | `00100` | OFF, OFF, ON, OFF, OFF  |
| `STATE_SENSOR_ERROR`  | `5` | `0x05` | `00101` | OFF, OFF, ON, OFF, ON   |
| `STATE_NETWORK_ERROR` | `6` | `0x06` | `00110` | OFF, OFF, ON, ON, OFF   |
| `STATE_OFFLINE`       | `7` | `0x07` | `00111` | OFF, OFF, ON, ON, ON    |

