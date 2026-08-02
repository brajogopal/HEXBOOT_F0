# Firmware Receiver

## Overview

The Firmware Receiver manages the firmware update process.

It receives firmware packets through DMA, parses the firmware header, determines which firmware image should be accepted, and controls the firmware reception state machine.

The module is independent of Flash programming and focuses solely on firmware reception.

---

## Features

- Firmware header parsing
- DMA-based reception
- Dual-slot packet support
- Selective payload reception
- Payload discard mechanism
- Chunk management
- Firmware reception state machine

---

## Files

```
firmware_receiver.c
firmware_receiver.h
```

---

## State Machine

```
PARSE_HEADER
      │
      ▼
DISCARD_PAYLOAD
      │
      ▼
RECEIVE_PAYLOAD
      │
      ▼
FW_COMPLETE

FW_ERROR
```

---

## Responsibilities

- Parse firmware header
- Extract firmware metadata
- Configure payload information
- Receive firmware through DMA
- Discard inactive firmware payload
- Track firmware reception progress

---

## Dependencies

- DMA Driver
- UART Driver
- Firmware Ping-Pong Module

---

## Used By

- Bootloader