# Metadata Module

## Overview

The Metadata module manages all persistent boot information stored in Flash.

It is responsible for creating, loading, validating, and saving the metadata required by the bootloader to determine firmware status and boot behavior.

Metadata is stored in a dedicated Flash region separate from the firmware slots.

---

## Features

- Metadata initialization
- Metadata loading
- Metadata saving
- Metadata verification
- Active slot management
- CRC protection

---

## Files

```
metadata.c
metadata.h
```

---

## Public API

| Function | Description |
|----------|-------------|
| `metadata_init()` | Initialize metadata and create default values if required |
| `metadata_load()` | Load metadata from Flash |
| `metadata_save()` | Save metadata to Flash |
| `metadata_verify()` | Verify metadata integrity |
| `metadata_get_active_slot()` | Return the active firmware slot |
| `metadata_set_active_slot()` | Update the active firmware slot |

---

## Metadata Layout

```
Magic Number
↓

Active Slot

↓

Boot State

↓

Boot Count

↓

Slot A Information

↓

Slot B Information

↓

Metadata CRC
```

---

## Dependencies

- Flash Driver
- CRC Driver

---

## Design Notes

- Stored in dedicated Flash memory
- Protected using CRC-16
- Automatically initialized on first boot
- Independent of firmware reception
- Independent of boot decision logic

---

## Used By

- Bootloader
- Slot Manager