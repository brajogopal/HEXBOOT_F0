# Bootloader

## Overview

The Bootloader is the central coordinator of the firmware update system.

It initializes all required modules, manages the firmware update process, verifies firmware integrity, updates metadata, and safely transfers execution to the selected application.

The bootloader itself does not implement Flash programming, DMA handling, metadata management, or slot selection. Instead, it coordinates these dedicated modules to perform the complete update process.

---

## Features

- Boot initialization
- Firmware update management
- Dual-slot fail-safe update
- CRC verification
- Metadata update
- Automatic rollback
- Safe application jump
- Update timeout protection

---

## Files

```
bootloader.c
bootloader.h
```

---

## Responsibilities

- Initialize bootloader modules
- Coordinate firmware reception
- Program firmware into Flash
- Verify firmware integrity
- Update metadata
- Select bootable application
- Jump to the application

---

## Bootloader State Machine

```
BOOT_WAIT_HEADER
        │
        ▼
BOOT_RECEIVE_FIRMWARE
        │
        ▼
BOOT_VERIFY
        │
        ▼
BOOT_JUMP
```

---

## Boot Sequence

1. Initialize drivers.
2. Initialize metadata.
3. Wait for firmware update.
4. Receive firmware.
5. Verify CRC.
6. Update metadata.
7. Jump to the selected application.

---

## Dependencies

### Drivers

- UART
- DMA
- Flash
- CRC
- SysTick
- BSP

### Bootloader Modules

- Metadata
- Slot Manager
- Firmware Receiver
- Firmware Ping-Pong

---

## Design Notes

- Register-level implementation
- No HAL
- No CubeMX
- Fail-safe boot process
- Dual-slot firmware architecture
- Automatic timeout recovery
- Modular architecture

---

## Used By

- `main()`