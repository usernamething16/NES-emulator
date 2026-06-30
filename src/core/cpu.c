#include "bus.h"
#include "cpu.h"
#include "cpu_internal.h"

void cpu_connect_bus(CPU *cpu, Bus *bus)
{
    cpu->bus = bus;
}

void cpu_clock(CPU *cpu)
{
    if (cpu->cycles == 0) {

    }
}

void cpu_reset(CPU *cpu)
{
    // start address of a 6502
    cpu->addr_abs = 0xFFFC;

    uint16_t lo = (uint16_t)bus_read(cpu->bus, cpu->addr_abs);
    uint16_t hi = (uint16_t)bus_read(cpu->bus, cpu->addr_abs + 1);

    cpu->pc = (hi << 8) | lo;

    cpu->a = 0;
    cpu->x = 0;
    cpu->y = 0;

    // top of the stack
    cpu->stkp = 0xFD;
    cpu->status = FLAG_U;

    cpu->addr_abs = 0x0000;
    cpu->addr_rel = 0x0000;
    cpu->fetched = 0x00;

    cpu->cycles = 8;
}

void cpu_irq(CPU *cpu)
{

}

void cpu_nmi(CPU *cpu)
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