#ifndef PPU_H
#define PPU_H

#include<stdint.h>

typedef struct Cartridge Cartridge;

typedef struct PPU {
    uint8_t ctrl; // PPUCTRL
    uint8_t mask; // PPUMASK
    uint8_t status; // PPUSTATUS
    uint8_t oam_addr; // OAMADDR

    uint8_t v;
    uint8_t t;
    uint8_t x;
    uint8_t w;
    uint8_t read_buffer;

    uint8_t vram[2 * 1024];
    uint8_t palette[32];
    uint8_t oam[256];

    uint32_t framebuffer[256 * 240]; 

    int16_t scanline;
    int16_t cycle;
    uint16_t frame;

    int frame_done;

    Cartridge *cart;
} PPU;

void ppu_init(PPU *ppu);
void ppu_connect_cartridge(PPU *ppu, Cartridge *cart);
void ppu_clock(PPU *ppu);

uint32_t ppu_color_from_palette(PPU *ppu, uint8_t palette, uint8_t pixel);
uint8_t ppu_read(PPU *ppu, uint16_t addr);
void ppu_write(PPU *ppu, uint16_t addr, uint8_t data);
void ppu_decode_tile(PPU *ppu, int table, int index, uint8_t out[64]);

#endif