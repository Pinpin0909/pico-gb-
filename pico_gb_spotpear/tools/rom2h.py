#!/usr/bin/env python3
"""
Convertit une ROM Game Boy (.gb/.gbc) en tableau C, pour l'embarquer
directement en flash du RP2040 (pas de lecteur microSD sur le module SpotPear).

Usage: python3 rom2h.py fichier.gb rom_data.h nom_du_tableau
"""
import sys

def main():
    if len(sys.argv) != 4:
        print("Usage: rom2h.py <in.gb> <out.h> <array_name>")
        sys.exit(1)

    in_path, out_path, array_name = sys.argv[1], sys.argv[2], sys.argv[3]

    with open(in_path, "rb") as f:
        data = f.read()

    guard = array_name.upper() + "_H"
    with open(out_path, "w") as f:
        f.write(f"// Genere automatiquement depuis {in_path} ({len(data)} octets)\n")
        f.write(f"#ifndef {guard}\n#define {guard}\n\n")
        f.write('#include "pico/platform.h"\n\n')
        f.write(f"#define {array_name.upper()}_SIZE {len(data)}u\n\n")
        f.write(f"static const unsigned char {array_name}[{array_name.upper()}_SIZE] __in_flash(\"rom\") __attribute__((aligned(4))) = {{\n")
        for i in range(0, len(data), 16):
            chunk = data[i:i+16]
            line = ", ".join(f"0x{b:02X}" for b in chunk)
            f.write(f"    {line},\n")
        f.write("};\n\n#endif\n")

    print(f"OK: {len(data)} octets -> {out_path}")

if __name__ == "__main__":
    main()
