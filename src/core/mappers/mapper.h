#ifndef MAPPER_H
#define MAPPER_H

#include <stdint.h>

typedef struct Mapper {
    uint8_t prg_banks;
    uint8_t chr_banks;
    
    
} Mapper;

void mapper000_init(Mapper *m, uint8_t prg_banks, uint8_t chr_banks);

#endif