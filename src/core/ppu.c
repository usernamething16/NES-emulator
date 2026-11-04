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

void ppu_clock(PPU *ppu)
{
    // vblank
    if (ppu->scanline == 241 && ppu->cycle == 1) {
        ppu->status |= 0x80;
        if (ppu->ctrl & 0x80)
            ppu->nmi = 1;
    }

    if (ppu->scanline == -1 && ppu->cycle == 1) {
        ppu->status &= ~0x80;
    }

    ppu->cycle++;
    if (ppu->cycle > 340) {
        ppu->cycle = 0;
        ppu->scanline++;
        if (ppu->scanline > 260) {
            ppu->scanline = -1;
            ppu->frame++;
            ppu->frame_done = 1;
        }
    }
}

void ppu_render_background(PPU *ppu)
{
    // notice: this is placeholder and only applies to table 0 (0x2000)
    // so no scrolling games like mario (or almost any other lol)
    
    for (int y = 0; y < 30; y++) {
        for (int x = 0; x < 32; x++) {
            uint8_t tile = ppu_read(ppu, 0x2000 + y * 32 + x);
            uint8_t attribute = ppu_read(ppu, 0x2000 + 960 + (y / 4) * 8 + (x / 4));
            int shift = ((y & 2) << 1) | (x & 2);
            uint8_t palette = (attribute >> shift) & 0x03;

            uint8_t pixels[64];
            int table = (ppu->ctrl & 0x10) ? 1 : 0;
            ppu_decode_tile(ppu, table, tile, pixels);

            for (int row = 0; row < 8; row++) {
                for(int col = 0; col < 8; col++) {
                    int px = x * 8 + col;
                    int py = y * 8 + row;
                    ppu->framebuffer[py * 256 + px] = ppu_color_from_palette(ppu, palette, pixels[row * 8 + col]);
                }
            }
        }
    }
}

uint32_t ppu_palette_argb(uint8_t nes_color)
{
    return nes_palette[nes_color & 0x3F];
}

uint32_t ppu_color_from_palette(PPU *ppu, uint8_t palette, uint8_t pixel)
{
    uint8_t idx = ppu_read(ppu, 0x3F00 + (palette * 4) + pixel);
    return ppu_palette_argb(idx);
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
    uint16_t base = (uint16_t)(table ? 0x1000 : 0x0000) + (uint16_t)(index * 16);

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

uint8_t ppu_cpu_read(PPU *ppu, uint16_t addr)
{
    uint8_t data = 0x00;

    switch (addr) {
    case PPUCRTL:
    case PPUMASK:
        break;

    case PPUSTATUS:
        data = (ppu->status & (0xE0)) | (ppu->read_buffer & (0x1F));
        ppu->status &= 0x7F;
        ppu->w = 0;
        break;
    
    case OAMADDR:
        break;
    
    case OAMDATA:
        data = ppu->oam[ppu->oam_addr];
        break;

    case PPUSCROLL:
    case PPUADDR:
        break;
    
    case PPUDATA:
        data = ppu->read_buffer;
        ppu->read_buffer = ppu_read(ppu, ppu->v & 0x2FFF);

        if (ppu->v >= 0x3F00)
            data = ppu->read_buffer;
        
        ppu->v += (ppu->ctrl & 0x04) ? 32 : 1;
        break;
    }

    return data;
}

void ppu_cpu_write(PPU *ppu, uint16_t addr, uint8_t data)
{
    switch (addr) {
    case PPUCRTL:
        ppu->ctrl = data;
        ppu->t = (ppu->t & 0xF3FF) | ((uint16_t)(data & 0x03) << 10);
        break;

    case PPUMASK:
        ppu->mask = data;
        break;

    case PPUSTATUS:
        break;
    
    case OAMADDR:
        ppu->oam_addr = data;
        break;
    
    case OAMDATA:
        ppu->oam[ppu->oam_addr++] = data; 
        break;

    case PPUSCROLL:
        if (ppu->w == 0) {
            ppu->x = data & 0x07;
            ppu->t = (ppu->t & 0xFFE0) |  (uint16_t)(data >> 3);
            ppu->w = 1;
        } else {
            ppu->t = (ppu->t & 0x8FFF) | ((uint16_t)(data & 0x07) << 12);
            ppu->t = (ppu->t & 0xFC1F) | ((uint16_t)(data >> 3) << 5);
            ppu->w = 0;
        }
        break;

    case PPUADDR:
        if (ppu->w == 0) {
            ppu->t = (ppu->t & 0x00FF) | ((uint16_t)(data & 0x3F) << 8);
            ppu->w = 1;
        } else {
            ppu->t = (ppu->t & 0xFF00) | (uint16_t)data;
            ppu->v = ppu->t;
            ppu->w = 0;
        }
        break;
    
    case PPUDATA:
        ppu_write(ppu, ppu->v, data);
        ppu->v += (ppu->ctrl & 0x04) ? 32 : 1;
        break;
    }
}
