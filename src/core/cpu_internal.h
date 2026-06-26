#ifndef CPU_INTERNAL_H
#define CPU_INTERNAL_H

#include<stdint.h>
#include "cpu.h"

typedef struct instruction {
    uint8_t opcode;
    uint8_t (*addrmode)(CPU *cpu);
    uint8_t (*operate)(CPU *cpu); 
    uint8_t cycles;
} instruction;

#endif