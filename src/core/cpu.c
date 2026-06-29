#include "cpu.h"

void cpu_connect_bus(CPU *cpu, Bus *bus)
{
    cpu->bus = bus;
}

void cpu_reset(CPU *cpu)
{

}

void cpu_irq(CPU *cpu)
{

}

void cpu_nmi(CPU *cpu)
{

}

void cpu_clock(CPU *cpu)
{

}

int cpu_complete(CPU *cpu)
{

}

uint8_t cpu_get_flag(CPU *cpu, Flags f)
{
    return (cpu->status & f) ? 1 : 0;
}

void cpu_set_flag(CPU *cpu, Flags f, uint8_t val)
{
    if (val)
        cpu->status |= f;
    else
        cpu->status &= ~f;
}