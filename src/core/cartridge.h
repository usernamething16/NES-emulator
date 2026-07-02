#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <stdint.h>

typedef struct Cartridge {
    uint8_t prg[32 * 1024];
    uint8_t chr[8 * 1024];
    uint8_t prg_banks;
    uint8_t chr_banks;
    int loaded;
} Cartridge;

int cartridge_load(Cartridge *cart, const char *path);
uint8_t cartridge_read(Cartridge *cart, uint16_t addr);
void cartridge_write(Cartridge *cart, uint16_t addr, uint8_t data);


#endif