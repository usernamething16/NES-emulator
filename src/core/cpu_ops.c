#include "cpu_internal.h"
#include "bus.h"

// ops
uint8_t ADC(CPU *cpu)
{
    return 0;
}

uint8_t AND(CPU *cpu)
{
    return 0;
}

uint8_t ASL(CPU *cpu)
{
    return 0;
}

uint8_t BCC(CPU *cpu)
{
    if (!cpu_get_flag(cpu, FLAG_C)) {
        cpu->cycles++;
        cpu->addr_abs = cpu->pc + cpu->addr_rel;

        if (cpu->addr_abs & 0xFF00 != cpu->pc & 0xFF00)
            cpu->cycles++;
        
        cpu->pc = cpu->addr_abs;
    }
    
    return 0;
}

uint8_t BCS(CPU *cpu)
{
    if (cpu_get_flag(cpu, FLAG_C)) {
        cpu->cycles++;
        cpu->addr_abs = cpu->pc + cpu->addr_rel;

        if (cpu->addr_abs & 0xFF00 != cpu->pc & 0xFF00)
            cpu->cycles++;
        
        cpu->pc = cpu->addr_abs;
    }

    return 0;
}

uint8_t BEQ(CPU *cpu)
{
    if (cpu_get_flag(cpu, FLAG_Z)) {
        cpu->cycles++;
        cpu->addr_abs = cpu->pc + cpu->addr_rel;

        if (cpu->addr_abs & 0xFF00 != cpu->pc & 0xFF00)
            cpu->cycles++;
        
        cpu->pc = cpu->addr_abs;
    }

    return 0;
}

uint8_t BIT(CPU *cpu)
{
    cpu_fetch(cpu);

    cpu_set_flag(cpu, FLAG_Z, (cpu->a & cpu->fetched) == 0);
    cpu_set_flag(cpu, FLAG_V, cpu->fetched & 0x40);
    cpu_set_flag(cpu, FLAG_N, cpu->fetched & 0x80);

    return 0;
}

uint8_t BMI(CPU *cpu)
{
    if (cpu_get_flag(cpu, FLAG_N)) {
        cpu->cycles++;
        cpu->addr_abs = cpu->pc + cpu->addr_rel;

        if (cpu->addr_abs & 0xFF00 != cpu->pc & 0xFF00)
            cpu->cycles++;
        
        cpu->pc = cpu->addr_abs;
    }

    return 0;
}

uint8_t BNE(CPU *cpu)
{
    if (!cpu_get_flag(cpu, FLAG_Z)) {
        cpu->cycles++;
        cpu->addr_abs = cpu->pc + cpu->addr_rel;

        if (cpu->addr_abs & 0xFF00 != cpu->pc & 0xFF00)
            cpu->cycles++;
        
        cpu->pc = cpu->addr_abs;
    }

    return 0;
}

uint8_t BPL(CPU *cpu)
{
    if (!cpu_get_flag(cpu, FLAG_N)) {
        cpu->cycles++;
        cpu->addr_abs = cpu->pc + cpu->addr_rel;

        if (cpu->addr_abs & 0xFF00 != cpu->pc & 0xFF00)
            cpu->cycles++;
        
        cpu->pc = cpu->addr_abs;
    }

    return 0;
}

uint8_t BRK(CPU *cpu)
{
    return 0;
}

uint8_t BVC(CPU *cpu)
{
    if (!cpu_get_flag(cpu, FLAG_V)) {
        cpu->cycles++;
        cpu->addr_abs = cpu->pc + cpu->addr_rel;

        if (cpu->addr_abs & 0xFF00 != cpu->pc & 0xFF00)
            cpu->cycles++;
        
        cpu->pc = cpu->addr_abs;
    }

    return 0;
}


uint8_t BVS(CPU *cpu)
{
    if (cpu_get_flag(cpu, FLAG_V)) {
        cpu->cycles++;
        cpu->addr_abs = cpu->pc + cpu->addr_rel;

        if (cpu->addr_abs & 0xFF00 != cpu->pc & 0xFF00)
            cpu->cycles++;
        
        cpu->pc = cpu->addr_abs;
    }

    return 0;
}

uint8_t CLC(CPU *cpu)
{
    cpu_set_flag(cpu, FLAG_C, 0);

    return 0;
}

uint8_t CLD(CPU *cpu)
{
    return 0;
}

uint8_t CLI(CPU *cpu)
{
    return 0;
}

uint8_t CLV(CPU *cpu)
{
    return 0;
}

uint8_t CMP(CPU *cpu)
{
    return 0;
}

uint8_t CPX(CPU *cpu)
{
    return 0;
}

uint8_t CPY(CPU *cpu)
{
    return 0;
}

uint8_t DEC(CPU *cpu)
{
    return 0;
}

uint8_t DEX(CPU *cpu)
{
    return 0;
}

uint8_t DEY(CPU *cpu)
{
    return 0;
}

uint8_t EOR(CPU *cpu)
{
    return 0;
}

uint8_t INC(CPU *cpu)
{
    return 0;
}

uint8_t INX(CPU *cpu)
{
    return 0;
}

uint8_t INY(CPU *cpu)
{
    return 0;
}

uint8_t JMP(CPU *cpu)
{
    cpu->pc = cpu->addr_abs;

    return 0;
}

uint8_t JSR(CPU *cpu)
{
    cpu->pc--;

    uint8_t hi = (cpu->pc >> 8) & 0x00FF;
    uint8_t lo = (cpu->pc & 0x00FF);

    bus_write(cpu->bus, 0x0100 + cpu->stkp, hi);
    cpu->stkp--;
    bus_write(cpu->bus, 0x0100 + cpu->stkp, lo);
    cpu->stkp--;

    cpu->pc = cpu->addr_abs;

    return 0;
}

uint8_t LDA(CPU *cpu)
{
    cpu_fetch(cpu);
    cpu->a = cpu->fetched;

    cpu_set_flag(cpu, FLAG_Z, cpu->a == 0x00);
    cpu_set_flag(cpu, FLAG_N, cpu->a & 0x80);

    return 1;
}

uint8_t LDX(CPU *cpu)
{
    cpu_fetch(cpu);
    cpu->x = cpu->fetched;

    cpu_set_flag(cpu, FLAG_Z, cpu->x == 0x00);
    cpu_set_flag(cpu, FLAG_N, cpu->x & 0x80);

    return 1;
}

uint8_t LDY(CPU *cpu)
{
    cpu_fetch(cpu);
    cpu->y = cpu->fetched;

    cpu_set_flag(cpu, FLAG_Z, cpu->y == 0x00);
    cpu_set_flag(cpu, FLAG_N, cpu->y & 0x80);

    return 1;
}

uint8_t LSR(CPU *cpu)
{
    return 0;
}

uint8_t NOP(CPU *cpu)
{
    (void)cpu;
    return 0;
}

uint8_t ORA(CPU *cpu)
{
    return 0;
}

uint8_t PHA(CPU *cpu)
{
    return 0;
}

uint8_t PHP(CPU *cpu)
{
    return 0;
}

uint8_t PLA(CPU *cpu)
{
    return 0;
}

uint8_t PLP(CPU *cpu)
{
    return 0;
}

uint8_t ROL(CPU *cpu)
{
    return 0;
}

uint8_t ROR(CPU *cpu)
{
    return 0;
}

uint8_t RTI(CPU *cpu)
{
    return 0;
}

uint8_t RTS(CPU *cpu)
{
    cpu->stkp++;
    uint16_t lo = bus_read(cpu->bus, 0x0100 + cpu->stkp);
    cpu->stkp++;
    uint16_t hi = bus_read(cpu->bus, 0x0100 + cpu->stkp);

    cpu->pc = ((hi << 8) | lo) + 1;

    return 0;
}

uint8_t SBC(CPU *cpu)
{
    return 0;
}

uint8_t SEC(CPU *cpu)
{
    cpu_set_flag(cpu, FLAG_C, 1);

    return 0;
}

uint8_t SED(CPU *cpu)
{
    cpu_set_flag(cpu, FLAG_D, 1);

    return 0;
}

uint8_t SEI(CPU *cpu)
{
    cpu_set_flag(cpu, FLAG_I, 1);

    return 0;
}

uint8_t STA(CPU *cpu)
{
    bus_write(cpu->bus, cpu->addr_abs, cpu->a);

    return 0;
}

uint8_t STX(CPU *cpu)
{
    bus_write(cpu->bus, cpu->addr_abs, cpu->x);
    return 0;
}

uint8_t STY(CPU *cpu)
{
    return 0;
}

uint8_t TAX(CPU *cpu)
{
    return 0;
}

uint8_t TAY(CPU *cpu)
{
    return 0;
}

uint8_t TSX(CPU *cpu)
{
    return 0;
}

uint8_t TXA(CPU *cpu)
{
    return 0;
}

uint8_t TXS(CPU *cpu)
{
    return 0;
}

uint8_t TYA(CPU *cpu)
{
    return 0;
}

// illegal ops
uint8_t XXX(CPU *cpu)
{
    return 0;
}
