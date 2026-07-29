#ifndef PPU_H
#define PPU_H

#include<stdint.h>

typedef struct Cartridge Cartridge;

typedef struct PPU {
    uint8_t vram[2 * 1024];
    uint8_t palette[32];
    uint8_t oam[256];

    Cartridge *cart;
} PPU;

void ppu_init(PPU *ppu);
void ppu_connect_cartridge(PPU *ppu, Cartridge *cart);
void ppu_clock(PPU *ppu);

uint8_t ppu_read(PPU *ppu, uint16_t addr);
void ppu_write(PPU *ppu, uint16_t addr, uint8_t data);


#endif