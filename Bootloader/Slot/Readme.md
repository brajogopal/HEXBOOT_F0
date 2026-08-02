# Slot Manager

## Overview

The Slot Manager is responsible for selecting and validating firmware slots within the dual-slot bootloader architecture.

It determines which application should be booted, identifies the inactive slot for firmware updates, and validates whether a firmware image is suitable for execution.

The module operates entirely on metadata and does not perform Flash programming or firmware reception.

---

## Features

- Active slot selection
- Inactive slot selection
- Firmware slot validation
- Bootable image selection
- Slot address retrieval
- Slot information access

---

## Files

```
slot_manager.c
slot_manager.h
```

---

## Public API

| Function | Description |
|----------|-------------|
| `slot_manager_get_active_slot()` | Return the currently active firmware slot |
| `slot_manager_get_inactive_slot()` | Return the inactive firmware slot |
| `slot_manager_get_slot_address()` | Return the Flash address of a slot |
| `slot_manager_get_slot_info()` | Return metadata associated with a slot |
| `slot_manager_is_bootable()` | Validate whether a slot can be booted |
| `slot_manager_select_boot_slot()` | Select the best firmware slot for booting |

---

## Dependencies

- Metadata Module
- UART Driver (debug messages)

---

## Design Notes

- Independent of Flash programming
- Independent of firmware reception
- Uses metadata for all boot decisions
- Returns descriptive status codes
- Implements fail-safe slot selection

---

## Boot Selection Logic

1. Check the active slot.
2. If the active slot is bootable, boot it.
3. Otherwise, check the inactive slot.
4. If the inactive slot is bootable, boot it.
5. If neither slot is valid, return `SLOT_NONE`.

---

## Used By

- Bootloader