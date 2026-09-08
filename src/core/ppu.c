#include "ppu.h"
#include <string.h>

void ppu_init(PPU *ppu)
{

}

void ppu_connect_cartridge(PPU *ppu, Cartridge *cart)
{
    ppu->cart = cart;
}

uint8_t ppu_read(PPU *ppu, uint16_t addr)
{

}

void ppu_write(PPU *ppu, uint16_t addr, uint8_t data)
{
    
}
