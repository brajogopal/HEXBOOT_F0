# UART Driver

## Overview

This module provides a lightweight register-level UART driver for the STM32F030C8T6.

The driver is primarily used for:

- Bootloader debug messages
- Firmware reception
- User interaction
- UART interrupt-based communication

No STM32 HAL or CubeMX generated code is used.

---

## Features

- UART initialization
- Configurable baud rate
- Character transmission
- String transmission
- Character reception
- Blocking string reception
- Receive timeout support
- UART interrupt initialization

---

## Files

```
uart.c
uart.h
```

---

## Public API

| Function | Description |
|----------|-------------|
| `debug_uart_init()` | Initialize UART for polling mode |
| `uart_interrupt_init()` | Initialize UART with RX interrupt enabled |
| `println()` | Send a string followed by CR/LF |
| `uart_receive_char()` | Receive a single character |
| `uart_receive_string()` | Receive a string until Enter is pressed |
| `uart_receive_with_timeout()` | Receive a character with timeout |

---

## Dependencies

- CMSIS
- RCC Driver

---

## Design Notes

- Register-level implementation only
- No HAL
- No CubeMX
- Uses USART2
- Supports both polling and interrupt operation
- Designed to be reusable across applications

---

## Used By

- Bootloader
- Firmware Receiver
- Debug Console