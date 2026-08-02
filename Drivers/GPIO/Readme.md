# GPIO Driver

## Overview

This module provides a lightweight register-level General Purpose Input/Output (GPIO) driver for the STM32F030C8T6.

It offers a simple and hardware-independent API for configuring and controlling GPIO pins while internally using CMSIS register access.

Board-specific pin assignments are intentionally kept outside this driver in the BSP module.

---

## Features

- GPIO pin configuration
- Digital output
- Digital input
- Pin toggle
- Generic pin abstraction

---

## Files

```
gpio.c
gpio.h
```

---

## Public API

| Function | Description |
|----------|-------------|
| `pinMode()` | Configure the operating mode of a GPIO pin |
| `digitalWrite()` | Set a GPIO output HIGH or LOW |
| `digitalRead()` | Read the logic level of a GPIO input |
| `togglePin()` | Toggle the current output state of a GPIO pin |

---

## Dependencies

- CMSIS

---

## Design Notes

- Register-level implementation
- No HAL
- No CubeMX
- Supports GPIOA, GPIOB, GPIOC and GPIOD
- Generic pin encoding using `pin_t`
- Independent of any specific hardware board

---

## Used By

- BSP
- Bootloader
- Test Applications