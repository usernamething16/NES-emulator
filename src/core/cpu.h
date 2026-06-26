#ifndef CPU_H
#define CPU_H

#include<stdint.h>

typedef struct CPU {
    // registers
    uint8_t a;
    uint8_t x;
    uint8_t y;
    uint8_t stkp; // stack pointer
    uint8_t status;

    uint16_t pc; // program counter

    uint8_t fetched;
    uint8_t opcode;
    uint8_t cycles;
    uint8_t addr_add;
    uint8_t addr_rel;


} CPU;

#endif