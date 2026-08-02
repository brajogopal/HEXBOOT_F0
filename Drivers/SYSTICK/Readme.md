# SysTick Driver

## Overview

This module provides a lightweight SysTick timer driver for the STM32F030C8T6.

It is used to generate a periodic system tick for timekeeping and timeout management throughout the project.

The driver is implemented entirely using CMSIS register access without relying on STM32 HAL or CubeMX.

---

## Features

- Configurable tick frequency
- Millisecond system tick generation
- System uptime counter
- Tick counter reset
- Interrupt-driven operation

---

## Files

```
systick.c
systick.h
```

---

## Public API

| Function | Description |
|----------|-------------|
| `systick_init()` | Initialize the SysTick timer |
| `systick_get_tick()` | Return the current system tick count |
| `systick_reset_tick()` | Reset the system tick counter |

---

## Dependencies

- CMSIS
- RCC Driver

---

## Design Notes

- Register-level implementation only
- Uses the Cortex-M SysTick peripheral
- Interrupt-driven tick generation
- No dynamic memory allocation
- Portable across Cortex-M devices

---

## Used By

- Bootloader
- Timeout Management
- Delay and Timing Functions
- Firmware Update Process