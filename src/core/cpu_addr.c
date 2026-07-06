#include "cpu_internal.h"
#include "bus.h"

// addressing modes

// implicit
uint8_t IMP(CPU *cpu)
{
    cpu->fetched = cpu->a;

    return 0;
}

// #v (immediate)
uint8_t IMM(CPU *cpu)
{
    cpu->addr_abs = cpu->pc;
    cpu->pc++;

    return 0;
}

// d (zero page)
uint8_t ZP0(CPU *cpu)
{
    cpu->addr_abs = bus_read(cpu->bus, cpu->pc);

    return 0;
}

// d,x (zero page offset by x)
uint8_t ZPX(CPU *cpu)
{
    cpu->addr_abs = (bus_read(cpu->bus, cpu->pc) + cpu->x) & 0x00FF;
    cpu->pc++;

    return 0;
}

// d,y (zero page offset by y)
uint8_t ZPY(CPU *cpu)
{
    cpu->addr_abs = (bus_read(cpu->bus, cpu->pc) + cpu->y) & 0x00FF;
    cpu->pc++;

    return 0;
}

// a (absolute)
uint8_t ABS(CPU *cpu)
{
    uint16_t lo = bus_read(cpu->bus, cpu->pc);
    cpu->pc++;
    uint16_t hi = bus_read(cpu->bus, cpu->pc);
    cpu->pc++;

    cpu->addr_abs = (hi << 8) | lo;

    return 0;
}

// a,x (absolute offset by x)
uint8_t ABX(CPU *cpu)
{
    uint16_t lo = bus_read(cpu->bus, cpu->pc);
    cpu->pc++;
    uint16_t hi = bus_read(cpu->bus, cpu->pc);
    cpu->pc++;

    cpu->addr_abs = (hi << 8) | lo + cpu->x;
    if ((cpu->addr_abs & 0xFF00) != (hi << 8))
        return 1;
    return 0;
}

// a,y (absolute offset by y)
uint8_t ABY(CPU *cpu)
{
    uint16_t lo = bus_read(cpu->bus, cpu->pc);
    cpu->pc++;
    uint16_t hi = bus_read(cpu->bus, cpu->pc);
    cpu->pc++;

    cpu->addr_abs = (hi << 8) | lo + cpu->y;
    if ((cpu->addr_abs & 0xFF00) != (hi << 8))
        return 1;
    return 0;
}

// label (relative)
uint8_t REL(CPU *cpu)
{
    cpu->addr_rel = bus_read(cpu->bus, cpu->pc);
    cpu->pc++;

    if (cpu->addr_rel & 0x80)
        cpu->addr_rel |= 0xFF00;

    return 0;
}

// (a) (indirect)
uint8_t IND(CPU *cpu)
{
    uint16_t lo = bus_read(cpu->bus, cpu->pc);
    cpu->pc++;

    return 0;
}

// (d,x) (indirect x)
uint8_t IZX(CPU *cpu)
{
    return 0;
}

// (d),y (indirect y)
uint8_t IZY(CPU *cpu)
{
    return 0;
}
