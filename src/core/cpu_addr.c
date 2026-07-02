#include "cpu_internal.h"
#include "bus.h"

// addressing modes

// implicit
uint8_t IMP(CPU *cpu)
{
    return 0;
}

// #v (immediate)
uint8_t IMM(CPU *cpu)
{
    return 0;
}

// d (zero page)
uint8_t ZP0(CPU *cpu)
{
    return 0;
}

// d,x (zero page offset by x)
uint8_t ZPX(CPU *cpu)
{
    return 0;
}

// d,y (zero page offset by y)
uint8_t ZPY(CPU *cpu)
{
    return 0;
}

// a (absolute)
uint8_t ABS(CPU *cpu)
{
    return 0;
}

// a,x (absolute offset by x)
uint8_t ABX(CPU *cpu)
{
    return 0;
}

// a,y (absolute offset by y)
uint8_t ABY(CPU *cpu)
{
    return 0;
}

// label (relative)
uint8_t REL(CPU *cpu)
{
    return 0;
}

// (a) (indirect)
uint8_t IND(CPU *cpu)
{
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
