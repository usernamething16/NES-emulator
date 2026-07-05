#ifndef CPU_H
#define CPU_H

#include <stdint.h>

typedef struct Bus Bus;

typedef enum {
    FLAG_C = (1 << 0), // carry bit
    FLAG_Z = (1 << 1), // zero
    FLAG_I = (1 << 2), // interrupt disable
    FLAG_D = (1 << 3), // decimal
    FLAG_B = (1 << 4), // break
    FLAG_U = (1 << 5), // unused
    FLAG_V = (1 << 6), // overflow
    FLAG_N = (1 << 7), // negative
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
    uint16_t addr_abs;
    uint16_t addr_rel;

    Bus *bus;
} CPU;

void cpu_connect_bus(CPU *cpu, Bus *bus);
uint8_t cpu_get_flag(CPU *cpu, Flags f);
void cpu_set_flag(CPU *cpu, Flags f, uint8_t val);
void cpu_reset(CPU *cpu);
void cpu_irq(CPU *cpu);
void cpu_nmi(CPU *cpu);
void cpu_clock(CPU *cpu);
int cpu_complete(const CPU *cpu);

#endif
