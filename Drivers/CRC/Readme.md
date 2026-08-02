# CRC Driver

## Overview

This module provides a software implementation of the CRC-16 checksum algorithm.

It is used to verify firmware integrity during the bootloader update process and ensures that firmware images stored in Flash have not been corrupted during transmission or programming.

The implementation is completely hardware-independent and can be reused across different microcontrollers and host-side tools.

---

## Features

- CRC-16 calculation
- Software implementation
- Platform independent
- Firmware integrity verification

---

## Files

```
crc.c
crc.h
```

---

## Public API

| Function | Description |
|----------|-------------|
| `crc16_calculate()` | Calculate the CRC-16 checksum of a data buffer |

---

## Dependencies

- Standard Integer Types (`stdint.h`)

---

## Design Notes

- Software implementation
- CRC-16 polynomial: `0x1021`
- No hardware CRC peripheral required
- No dynamic memory allocation
- Portable across platforms

---

## Used By

- Firmware Receiver
- Bootloader Verification
- Metadata Validation