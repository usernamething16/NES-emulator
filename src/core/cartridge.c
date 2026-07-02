#include "cartridge.h"
#include <stdio.h>
#include <string.h>

int cartridge_load(Cartridge *cart, const char *path)
{
    FILE *f = fopen(path, "rb");
    if (!f)
        return 1;

    uint8_t header[16];

    if (fread(header, 1, sizeof header, f) != sizeof header) {
        fclose(f);
        return 1;
    }

    if (header[0] != 'N' || header[1] != 'E' ||
        header[2] != 'S' || header[3] != 0x1A) {
        fclose(f);
        return 1;
    }

    cart->prg_banks = header[4];
    cart->chr_banks = header[5];

    if (header[6] & 0x04) fseek(f, 512, SEEK_CUR);

    size_t prg_size = (size_t)cart->prg_banks * 16 * 1024;
    if (prg_size == 0 || prg_size > sizeof cart->prg) {
        fclose(f);
        return 1;
    }
    memset(cart->prg, 0, sizeof cart->prg);
    if (fread(cart->prg, 1, prg_size, f) != prg_size) {
        fclose(f);
        return 1;
    }

    size_t chr_size = (size_t)cart->prg_banks * 8 * 1024;
    if (chr_size > sizeof cart->chr)
        chr_size = sizeof cart->chr;
    memset(cart->chr, 0, sizeof cart->chr);
    if (chr_size) {if (fread(cart->chr, 1, chr_size, f) != chr_size) { } }

    fclose(f);
    cart->loaded = 1;
    return 0;
}

uint8_t cartridge_read(Cartridge *cart, uint16_t addr)
{
    if (addr >= 0x8000) {
        uint16_t mask = (cart->prg_banks > 1) ? 0x7FFF : 0x3FFF;
        return cart->prg[addr & mask];
    }
    return 0x00;
}

void cartridge_write(Cartridge *cart, uint16_t addr, uint8_t data)
{
    (void)cart; (void)addr; (void)data;
}
