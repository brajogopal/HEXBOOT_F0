# DMA Driver

## Overview

This module provides a lightweight DMA driver for UART reception on the STM32F030C8T6.

The driver is responsible for configuring DMA transfers, reporting transfer events, and remaining completely independent of application-specific logic.

DMA completion and error events are exposed through status flags, allowing higher-level modules such as the bootloader to coordinate firmware reception.

---

## Features

- DMA initialization
- UART RX DMA support
- Transfer complete notification
- Transfer error notification
- Interrupt-driven operation

---

## Files

```
dma.c
dma.h
```

---

## Public API

| Function | Description |
|----------|-------------|
| `dma_init()` | Initialize DMA for UART reception |
| `dma_receive()` | Start a DMA reception |
| `dma_get_transfer_complete()` | Check whether a transfer has completed |
| `dma_clear_transfer_complete()` | Clear the transfer complete flag |
| `dma_get_transfer_error()` | Check whether a transfer error occurred |
| `dma_clear_transfer_error()` | Clear the transfer error flag |

---

## Dependencies

- CMSIS

---

## Design Notes

- Register-level implementation
- Interrupt-driven DMA reception
- Reports events using status flags
- No callbacks
- No HAL
- No dynamic memory allocation
- Independent of bootloader logic

---

## Used By

- Firmware Receiver
- Bootloader