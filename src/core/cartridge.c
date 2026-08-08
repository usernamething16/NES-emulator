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

    cart->mapper_id = (header[7] & 0xF0) | (header[6] >> 4);
    cart->mirror = (header[6] & 0x01) ? MIRROR_VERTICAL : MIRROR_HORIZONTAL;  

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

    switch (cart->mapper_id) {
        case 0: mapper000_init(&cart->mapper, cart->prg_banks, cart->chr_banks); break;
        default: fclose(f); return 1;
    }

    fclose(f);
    cart->loaded = 1;

    return 0;
}

uint8_t cartridge_cpu_read(Cartridge *cart, uint16_t addr)
{
    uint32_t mapped;
    if (cart->mapper.cpu_map_read(&cart->mapper, addr, &mapped))
        return cart->prg[mapped];
    return 0x00;
}

void cartridge_cpu_write(Cartridge *cart, uint16_t addr, uint8_t data)
{
    uint32_t mapped;
    if (cart->mapper.cpu_map_write(&cart->mapper, addr, &mapped)) {
        (void)mapped;
        (void)data;
    }
}

uint8_t cartridge_ppu_read(Cartridge *cart, uint16_t addr)
{
    uint32_t mapped;
    if (cart->mapper.ppu_map_read(&cart->mapper, addr, &mapped)) {
        return cart->chr[mapped];
    }
    return 0x00;
}

void cartridge_ppu_write(Cartridge *cart, uint16_t addr, uint8_t data)
{
    uint32_t mapped;
    if (cart->mapper.ppu_map_write(&cart->mapper, addr, &mapped))
        cart->chr[mapped] = data;
}
