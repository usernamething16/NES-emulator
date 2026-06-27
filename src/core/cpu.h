#ifndef CPU_H
#define CPU_H

#include<stdint.h>

typedef struct Bus {} Bus;

typedef enum {
    C = (1 << 0), // carry bit
    Z = (1 << 1), // zero
    I = (1 << 2), // interrupt disable
    D = (1 << 3), // decimal
    B = (1 << 4), // break
    U = (1 << 5), // unused
    V = (1 << 6), // overflow
    N = (1 << 7), // negative
} Flags;

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

    Bus *bus;
} CPU;

void cpu_connect_bus(CPU *cpu, Bus *bus);
void cpu_reset(CPU *cpu);
void cpu_irq(CPU *cpu);
void cpu_nmi(CPU *cpu);
void cpu_clock(CPU *cpu);
int cpu_complete(CPU *cpu);
uint8_t cpu_get_flag(CPU *cpu, Flags f);
void cpu_set_flag(CPU *cpu, Flags f, uint8_t val);



#endif