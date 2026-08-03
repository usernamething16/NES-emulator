#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <stdint.h>
#include "mappers/mapper.h"

typedef enum {
    MIRROR_HORIZONTAL = 0,
    MIRROR_VERTICAL = 1,
} Mirror;

typedef struct Cartridge {
    uint8_t prg[32 * 1024];
    uint8_t chr[8 * 1024];
    uint8_t prg_banks;
    uint8_t chr_banks;
    uint8_t mapper_id;
    Mirror mirror;
    Mapper mapper;
    int loaded;
} Cartridge;

int cartridge_load(Cartridge *cart, const char *path);

uint8_t cartridge_cpu_read(Cartridge *cart, uint16_t addr);
void cartridge_cpu_write(Cartridge *cart, uint16_t addr, uint8_t data);

uint8_t cartridge_ppu_read(Cartridge *cart, uint16_t addr);
void cartridge_ppu_write(Cartridge *cart, uint16_t addr, uint8_t data);

#endif