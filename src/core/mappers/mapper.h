#ifndef MAPPER_H
#define MAPPER_H

#include <stdint.h>

typedef struct Mapper {
    uint8_t prg_banks;
    uint8_t chr_banks;
    
    int (*cpu_map_read)(struct Mapper *m, uint16_t addr, uint32_t *mapped);
    int (*cpu_map_write)(struct Mapper *m, uint16_t addr, uint32_t *mapped);
    int (*ppu_map_read)(struct Mapper *m, uint16_t addr, uint32_t *mapped);
    int (*ppu_map_write)(struct Mapper *m, uint16_t addr, uint32_t *mapped);
    
} Mapper;

void mapper000_init(Mapper *m, uint8_t prg_banks, uint8_t chr_banks);

#endif