# Flash Driver

## Overview

This module provides a register-level driver for the internal Flash memory of the STM32F030C8T6.

It supports Flash page erasing and half-word programming while handling Flash unlocking, locking, busy polling, verification, and error reporting internally.

The driver is designed specifically for bootloader and firmware update applications.

---

## Features

- Flash page erase
- Half-word programming
- Buffer programming
- Automatic Flash unlock/lock
- Busy timeout protection
- Write verification
- Detailed status reporting

---

## Files

```
flash.c
flash.h
```

---

## Public API

| Function | Description |
|----------|-------------|
| `flash_erase()` | Erase one or more Flash pages |
| `flash_program()` | Program a buffer into Flash memory |

---

## Status Codes

The driver returns a `flash_status_t` value to indicate the result of every operation.

Possible return values include:

- `FLASH_OK`
- `FLASH_TIMEOUT`
- `FLASH_PG_ERROR`
- `FLASH_WRP_ERROR`
- `FLASH_VERIFY_ERROR`
- `FLASH_ERROR`

---

## Dependencies

- CMSIS

---

## Design Notes

- Register-level implementation
- Automatic Flash unlock and lock
- Automatic busy polling
- Internal write verification
- No HAL
- No dynamic memory allocation

---

## Used By

- Bootloader
- Firmware Update Module
- Metadata Module