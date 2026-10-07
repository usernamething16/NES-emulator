#include "ppu.h"
#include "cartridge.h"
#include <string.h>

static const uint32_t nes_palette[64] = {
    0xFF545454, 0xFF001E74, 0xFF081090, 0xFF300088, 0xFF440064, 0xFF5C0030,
    0xFF540400, 0xFF3C1800, 0xFF202A00, 0xFF083A00, 0xFF004000, 0xFF003C00,
    0xFF00323C, 0xFF000000, 0xFF000000, 0xFF000000,
    0xFF989698, 0xFF084CC4, 0xFF3032EC, 0xFF5C1EE4, 0xFF8814B0, 0xFFA01464,
    0xFF982220, 0xFF783C00, 0xFF545A00, 0xFF287200, 0xFF087C00, 0xFF007628,
    0xFF006678, 0xFF000000, 0xFF000000, 0xFF000000,
    0xFFECEEEC, 0xFF4C9AEC, 0xFF787CEC, 0xFFB062EC, 0xFFE454EC, 0xFFEC58B4,
    0xFFEC6A64, 0xFFD48820, 0xFFA0AA00, 0xFF74C400, 0xFF4CD020, 0xFF38CC6C,
    0xFF38B4CC, 0xFF3C3C3C, 0xFF000000, 0xFF000000,
    0xFFECEEEC, 0xFFA8CCEC, 0xFFBCBCEC, 0xFFD4B2EC, 0xFFECAEEC, 0xFFECAED4,
    0xFFECB4B0, 0xFFE4C490, 0xFFCCD278, 0xFFB4DE78, 0xFFA8E290, 0xFF98E2B4,
    0xFFA0D6E4, 0xFFA0A2A0, 0xFF000000, 0xFF000000,
};

void ppu_init(PPU *ppu)
{
    memset(ppu, 0, sizeof *ppu);
    ppu->scanline = -1;
}

void ppu_connect_cartridge(PPU *ppu, Cartridge *cart)
{
    ppu->cart = cart;
}

uint32_t ppu_palate_argb(uint8_t nes_color)
{
    return nes_palette[nes_color & 0x3F];
}

uint8_t ppu_read(PPU *ppu, uint16_t addr)
{
    addr &= 0x3FFF;

    if (addr <= 0x1FFF) {
        return cartridge_ppu_read(ppu->cart, addr);
    } else if (addr <= 0x3EFF) {
        addr &= 0x0FFF;
        int table = addr / 1024;
        int bank;

        if (ppu->cart->mirror == MIRROR_VERTICAL) {
            bank = (table == 0 || table == 2) ? 0 : 1;
        } else {
            bank = (table == 0 || table == 1) ? 0 : 1;
        }

        return ppu->vram[bank * 1024 + (addr & 0x03FF)];
    } else if (addr <= 0x3FFF) {
        addr &= 0x001F;

        //mirroring every first color
        if (addr >= 0x10 && (addr & 0x03) == 0)
            addr -= 0x10;

        return ppu->palette[addr];
    }
    return 0x00;
}

void ppu_write(PPU *ppu, uint16_t addr, uint8_t data)
{
    addr &= 0x3FFF;

    if (addr <= 0x1FFF) {
        cartridge_ppu_write(ppu->cart, addr, data);
        return;
    } else if (addr <= 0x3EFF) {
        addr &= 0x0FFF;
        int table = addr / 1024;
        int bank;

        if (ppu->cart->mirror == MIRROR_VERTICAL) {
            bank = (table == 0 || table == 2) ? 0 : 1;
        } else {
            bank = (table == 0 || table == 1) ? 0 : 1;
        }

        ppu->vram[bank * 1024 + (addr & 0x03FF)] = data;
    } else if (addr <= 0x3FFF) {
        addr &= 0x001F;

        //mirroring every first color
        if (addr >= 0x10 && (addr & 0x03) == 0)
            addr -= 0x10;

        ppu->palette[addr] = data;
    }
}

void ppu_decode_tile(PPU *ppu, int table, int index, uint8_t out[64])
{
    uint16_t base = (uint16_t)(table ? 1 : 0) + (uint16_t)(index * 16);

    for (int row = 0; row < 8; row++) {
        uint8_t plane0 = ppu_read(ppu, base + row);
        uint8_t plane1 = ppu_read(ppu, base + row + 8);

        for (int col = 0; col < 8; col++) {
            uint8_t lo = (plane0 >> (7 - col)) & 1;
            uint8_t hi = (plane1 >> (7 - col)) & 1;

            out[row * 8 + col] = (hi << 1 | lo);
        }
    }
}
