#include "bus.h"
#include "cpu_internal.h"

void cpu_connect_bus(CPU *cpu, Bus *bus)
{
    cpu->bus = bus;
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

void cpu_clock(CPU *cpu)
{
    if (cpu->cycles == 0) {
        cpu->opcode = bus_read(cpu->bus, cpu->pc);
        cpu->pc++;
        cpu_set_flag(cpu, FLAG_U, 1);

        instruction instr = cpu_lookup[cpu->opcode];
        uint8_t addr_ret = instr.addrmode(cpu);
        uint8_t op_ret = instr.operate(cpu);

        cpu->cycles += (addr_ret & op_ret);

        cpu_set_flag(cpu, FLAG_U, 1);
    }
    cpu->cycles--;
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
    cpu->status = FLAG_U | FLAG_I;

    cpu->addr_abs = 0x0000;
    cpu->addr_rel = 0x0000;
    cpu->fetched = 0x00;

    cpu->cycles = 8;
}

void cpu_irq(CPU *cpu)
{
    if (cpu_get_flag(cpu, FLAG_I) != 0)
        return;
    
    bus_write(cpu->bus, 0x0100 + cpu->stkp, (cpu->pc >> 8) & 0x00FF);
    cpu->stkp--;
    bus_write(cpu->bus, 0x0100 + cpu->stkp, cpu->pc & 0x00FF);
    cpu->stkp--;

    cpu_set_flag(cpu, FLAG_B, 0);
    cpu_set_flag(cpu, FLAG_I, 1);
    cpu_set_flag(cpu, FLAG_U, 1);

    bus_write(cpu->bus, 0x0100 + cpu->stkp, cpu->status);
    cpu->stkp--;

    cpu->addr_abs = 0xFFFE;
    uint16_t lo = bus_read(cpu->bus, cpu->addr_abs);
    uint16_t hi = bus_read(cpu->bus, cpu->addr_abs + 1);

    cpu->pc = (hi << 8) | lo;

    cpu->cycles = 7;
}

void cpu_nmi(CPU *cpu)
{
    bus_write(cpu->bus, 0x0100 + cpu->stkp, (cpu->pc >> 8) & 0x00FF);
    cpu->stkp--;
    bus_write(cpu->bus, 0x0100 + cpu->stkp, cpu->pc & 0x00FF);
    cpu->stkp--;

    cpu_set_flag(cpu, FLAG_B, 0);
    cpu_set_flag(cpu, FLAG_I, 1);
    cpu_set_flag(cpu, FLAG_U, 1);

    bus_write(cpu->bus, 0x0100 + cpu->stkp, cpu->status);
    cpu->stkp--;

    cpu->addr_abs = 0xFFFA;
    uint16_t lo = bus_read(cpu->bus, cpu->addr_abs);
    uint16_t hi = bus_read(cpu->bus, cpu->addr_abs + 1);

    cpu->pc = (hi << 8) | lo;

    cpu->cycles = 7;
}

int cpu_complete(const CPU *cpu)
{
    return cpu->cycles == 0;
}
