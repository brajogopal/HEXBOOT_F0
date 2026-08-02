# Delay Driver

## Overview

This module provides simple blocking delay functions using TIM1.

The driver is intended for timing operations where CPU blocking is acceptable,
such as LED blinking, simple demonstrations, and peripheral initialization.

---

## Features

- Millisecond delay
- Second delay
- Timer-based implementation
- Register-level programming

---

## Files

```
delay.c
delay.h
```

---

## Public API

| Function | Description |
|----------|-------------|
| `delay_ms()` | Generate a blocking delay in milliseconds |
| `delay()` | Generate a blocking delay in seconds |

---

## Dependencies

- CMSIS

---

## Design Notes

- Uses TIM1
- Blocking implementation
- No interrupts
- No HAL
- No dynamic memory allocation

---

## Used By

- Test Applications
- LED Demonstrations
- Peripheral Initialization