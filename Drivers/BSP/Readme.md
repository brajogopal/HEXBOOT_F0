# Board Support Package (BSP)

## Overview

This module provides board-specific configuration for the STM32F030C8T6 hardware used throughout this project.

The BSP defines the physical pin assignments for on-board peripherals and performs the initial hardware configuration required by the application.

Hardware-independent functionality is intentionally kept inside the peripheral drivers, while board-specific details remain in this module.

---

## Features

- Board initialization
- LED pin definition
- Push button pin definition
- Hardware abstraction

---

## Files

```
bsp.c
bsp.h
```

---

## Public API

| Function | Description |
|----------|-------------|
| `bsp_init()` | Initialize all board-specific peripherals |

---

## Board Configuration

| Peripheral | GPIO Pin |
|------------|----------|
| Status LED | PA5 |
| Push Button | PA6 |

---

## Dependencies

- GPIO Driver

---

## Design Notes

- Contains only board-specific information
- Independent of application logic
- No HAL
- No CubeMX
- Easy to adapt for different hardware by modifying only the BSP

---

## Used By

- Bootloader
- Test Applications