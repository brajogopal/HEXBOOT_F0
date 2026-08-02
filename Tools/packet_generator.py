"""
packet_generator.py

Creates a combined firmware package for HEXBOOT_F0.

Output Format:

+----------------------+
| Header (10 Bytes)    |
+----------------------+
| Slot A Firmware      |
+----------------------+
| Slot B Firmware      |
+----------------------+
"""

import os
import struct
from tkinter import Tk, filedialog

# ==========================================================
# Configuration
# ==========================================================

FW_HEADER = 0xAA

CRC16_POLY = 0x1021
CRC16_INIT = 0xFFFF


# ==========================================================
# CRC16 (Matches STM32 crc16_calculate())
# ==========================================================

def crc16_calculate(data: bytes) -> int:
    crc = CRC16_INIT

    for byte in data:

        crc ^= (byte << 8)

        for _ in range(8):

            if crc & 0x8000:
                crc = ((crc << 1) ^ CRC16_POLY) & 0xFFFF
            else:
                crc = (crc << 1) & 0xFFFF

    return crc


# ==========================================================
# Firmware Information
# ==========================================================

def firmware_info(path):

    with open(path, "rb") as f:
        data = f.read()

    return {
        "path": path,
        "data": data,
        "size": len(data),
        "crc": crc16_calculate(data)
    }


# ==========================================================
# Header Creation
# ==========================================================

def create_header(slot_a, slot_b):

    return struct.pack(
        "<BBHHHH",
        FW_HEADER,
        0x00,
        slot_a["size"],
        slot_b["size"],
        slot_a["crc"],
        slot_b["crc"]
    )


# ==========================================================
# Main
# ==========================================================

def main():

    Tk().withdraw()

    print("Select Slot A Firmware")

    slot_a_path = filedialog.askopenfilename(
        title="Select Slot A Firmware",
        filetypes=[("Binary Files", "*.bin")]
    )

    if not slot_a_path:
        print("Slot A not selected.")
        return


    print("Select Slot B Firmware")

    slot_b_path = filedialog.askopenfilename(
        title="Select Slot B Firmware",
        filetypes=[("Binary Files", "*.bin")]
    )

    if not slot_b_path:
        print("Slot B not selected.")
        return


    slot_a = firmware_info(slot_a_path)
    slot_b = firmware_info(slot_b_path)

    header = create_header(slot_a, slot_b)


    output_file = filedialog.asksaveasfilename(
        title="Save Combined Firmware",
        initialfile="combined_firmware.bin",
        defaultextension=".bin",
        filetypes=[("Binary Files", "*.bin")]
    )

    if not output_file:
        print("Output file not selected.")
        return


    with open(output_file, "wb") as f:

        f.write(header)
        f.write(slot_a["data"])
        f.write(slot_b["data"])


    print()
    print("=" * 50)
    print("HEXBOOT_F0 Packet Generated")
    print("=" * 50)

    print()
    print("Slot A")
    print("----------------------------------------")
    print(f"File : {os.path.abspath(slot_a['path'])}")
    print(f"Size : {slot_a['size']} bytes")
    print(f"CRC  : 0x{slot_a['crc']:04X}")

    print()

    print("Slot B")
    print("----------------------------------------")
    print(f"File : {os.path.abspath(slot_b['path'])}")
    print(f"Size : {slot_b['size']} bytes")
    print(f"CRC  : 0x{slot_b['crc']:04X}")

    print()

    print("Output")
    print("----------------------------------------")
    print(f"File        : {os.path.abspath(output_file)}")
    print(f"Header Size : {len(header)} bytes")
    print(f"Total Size  : {len(header) + slot_a['size'] + slot_b['size']} bytes")

    print()
    print("Packet Format")
    print("----------------------------------------")
    print("Header (10 Bytes)")
    print("Slot A Firmware")
    print("Slot B Firmware")


if __name__ == "__main__":
    main()