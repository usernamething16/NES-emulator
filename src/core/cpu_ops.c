#include "cpu_internal.h"
#include "bus.h"

// ops
uint8_t ADC(CPU *cpu)
{
    cpu_fetch(cpu);
    uint16_t result = (uint16_t)cpu->a + cpu->fetched + (cpu->status & FLAG_C);

    cpu_set_flag(cpu, FLAG_C, result > 0x00FF);
    cpu_set_flag(cpu, FLAG_Z, (result & 0x00FF) == 0);
    cpu_set_flag(cpu, FLAG_V, (result ^ cpu->a) & (result ^ cpu->fetched) & 0x80);
    cpu_set_flag(cpu, FLAG_N, result & 0x80);

    cpu->a = result & 0x00FF;

    return 1;
}

uint8_t AND(CPU *cpu)
{
    cpu_fetch(cpu);
    cpu->a &= cpu->fetched;
    

    cpu_set_flag(cpu, FLAG_Z, cpu->a == 0);
    cpu_set_flag(cpu, FLAG_N, cpu->a & 0x80);

    return 1;
}

uint8_t ASL(CPU *cpu)
{
    cpu_set_flag(cpu, FLAG_C, cpu->a & 0x80);
    cpu->a <<= 1;

    cpu_set_flag(cpu, FLAG_Z, cpu->a == 0);
    cpu_set_flag(cpu, FLAG_N, cpu->a & 0x80);

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

    return 1;
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
    cpu_set_flag(cpu, FLAG_D, 0);

    return 0;
}

uint8_t CLI(CPU *cpu)
{
    cpu_set_flag(cpu, FLAG_I, 0);

    return 0;
}

uint8_t CLV(CPU *cpu)
{
    cpu_set_flag(cpu, FLAG_V, 0);

    return 0;
}

uint8_t CMP(CPU *cpu)
{
    cpu_fetch(cpu);
    uint16_t result = (uint16_t)cpu->a - (uint16_t)cpu->fetched;

    cpu_set_flag(cpu, FLAG_C, cpu->a >= cpu->fetched);
    cpu_set_flag(cpu, FLAG_Z, (result & 0x00FF) == 0);
    cpu_set_flag(cpu, FLAG_N, result & 0x80);

    return 1;
}

uint8_t CPX(CPU *cpu)
{
    cpu_fetch(cpu);
    uint16_t result = (uint16_t)cpu->x - (uint16_t)cpu->fetched;

    cpu_set_flag(cpu, FLAG_C, cpu->x >= cpu->fetched);
    cpu_set_flag(cpu, FLAG_Z, (result & 0x00FF) == 0);
    cpu_set_flag(cpu, FLAG_N, result & 0x80);

    return 1;
}

uint8_t CPY(CPU *cpu)
{
    cpu_fetch(cpu);
    uint16_t result = (uint16_t)cpu->y - (uint16_t)cpu->fetched;

    cpu_set_flag(cpu, FLAG_C, cpu->y >= cpu->fetched);
    cpu_set_flag(cpu, FLAG_Z, (result & 0x00FF) == 0);
    cpu_set_flag(cpu, FLAG_N, result & 0x80);

    return 1;
}

uint8_t DEC(CPU *cpu)
{
    return 0;
}

uint8_t DEX(CPU *cpu)
{
    cpu->x--;

    cpu_set_flag(cpu, FLAG_Z, cpu->x == 0);
    cpu_set_flag(cpu, FLAG_N, cpu->x & 0x80);

    return 0;
}

uint8_t DEY(CPU *cpu)
{
    cpu->y--;

    cpu_set_flag(cpu, FLAG_Z, cpu->y == 0);
    cpu_set_flag(cpu, FLAG_N, cpu->y & 0x80);

    return 0;
}

uint8_t EOR(CPU *cpu)
{
    cpu_fetch(cpu);
    cpu->a ^= cpu->fetched;
    
    cpu_set_flag(cpu, FLAG_Z, cpu->a == 0);
    cpu_set_flag(cpu, FLAG_N, cpu->a & 0x80);

    return 1;
}

uint8_t INC(CPU *cpu)
{
    cpu_fetch(cpu);
    //bus_write(cpu->bus, cpu->addr_abs, cpu->fetched + 1);

    return 1;
}

uint8_t INX(CPU *cpu)
{
    cpu->x++;

    cpu_set_flag(cpu, FLAG_Z, cpu->x == 0);
    cpu_set_flag(cpu, FLAG_N, cpu->x & 0x80);

    return 0;
}

uint8_t INY(CPU *cpu)
{
    cpu->y++;

    cpu_set_flag(cpu, FLAG_Z, cpu->y == 0);
    cpu_set_flag(cpu, FLAG_N, cpu->y & 0x80);

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
    cpu_set_flag(cpu, FLAG_C, cpu->a & 0x01);
    cpu->a >>= 1;

    cpu_set_flag(cpu, FLAG_Z, cpu->a == 0);
    cpu_set_flag(cpu, FLAG_N, 0);

    return 0;
}

uint8_t NOP(CPU *cpu)
{
    (void)cpu;
    return 0;
}

uint8_t ORA(CPU *cpu)
{
    cpu_fetch(cpu);
    cpu->a |= cpu->fetched;

    cpu_set_flag(cpu, FLAG_Z, cpu->a == 0);
    cpu_set_flag(cpu, FLAG_N, cpu->a & 0x80);

    return 1;
}

uint8_t PHA(CPU *cpu)
{
    bus_write(cpu->bus, 0x0100 + cpu->stkp, cpu->a);
    cpu->stkp--;

    return 0;
}

uint8_t PHP(CPU *cpu)
{
    bus_write(cpu->bus, 0x0100 + cpu->stkp, cpu->status | FLAG_B | FLAG_U);
    cpu->stkp--;

    // todo: we potentially have to set the flags as well

    return 0;
}

uint8_t PLA(CPU *cpu)
{
    cpu->stkp++;
    cpu->a = bus_read(cpu->bus, 0x0100 + cpu->stkp);

    cpu_set_flag(cpu->bus, FLAG_Z, cpu->a == 0);
    cpu_set_flag(cpu->bus, FLAG_N, cpu->a & 0x80);

    return 0;
}

uint8_t PLP(CPU *cpu)
{
    cpu->stkp++;
    cpu->status = bus_read(cpu->bus, 0x0100 + cpu->stkp);

    cpu_set_flag(cpu, FLAG_B, 0);
    cpu_set_flag(cpu, FLAG_U, 1);

    return 0;
}

uint8_t ROL(CPU *cpu)
{
    uint8_t old_C = cpu_get_flag(cpu, FLAG_C);
    cpu_set_flag(cpu, FLAG_C, cpu->a & 0x80);
    cpu->a <<= 1;
    cpu->a |= old_C;

    cpu_set_flag(cpu, FLAG_Z, cpu->a == 0);
    cpu_set_flag(cpu, FLAG_N, cpu->a & 0x80);

    return 0;
}

uint8_t ROR(CPU *cpu)
{
    uint8_t old_C = cpu_get_flag(cpu, FLAG_C);
    cpu_set_flag(cpu, FLAG_C, cpu->a & 0x01);
    cpu->a >>= 1;
    cpu->a |= (old_C << 7);

    cpu_set_flag(cpu, FLAG_Z, cpu->a == 0);
    cpu_set_flag(cpu, FLAG_N, cpu->a & 0x80);

    return 0;
}

uint8_t RTI(CPU *cpu)
{
    cpu->stkp++;
    uint8_t flags = bus_read(cpu->bus, 0x0100 + cpu->stkp);
    cpu->stkp++;
    uint16_t lo = bus_read(cpu->bus, 0x0100 + cpu->stkp);
    cpu->stkp++;
    uint16_t hi = bus_read(cpu->bus, 0x0100 + cpu->stkp);

    cpu->pc = (hi << 8) | lo;

    cpu_set_flag(cpu, FLAG_N, flags & FLAG_N);
    cpu_set_flag(cpu, FLAG_V, flags & FLAG_V);
    cpu_set_flag(cpu, FLAG_B, 0);
    cpu_set_flag(cpu, FLAG_U, 1);
    cpu_set_flag(cpu, FLAG_D, flags & FLAG_D);
    cpu_set_flag(cpu, FLAG_I, flags & FLAG_I);
    cpu_set_flag(cpu, FLAG_Z, flags & FLAG_Z);
    cpu_set_flag(cpu, FLAG_C, flags & FLAG_C);

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
    cpu_fetch(cpu);
    uint16_t result = (uint16_t)cpu->a + ((uint16_t)cpu->fetched ^ 0x00FF) + (cpu->status & FLAG_C);

    cpu_set_flag(cpu, FLAG_C, result > 0xFF);
    cpu_set_flag(cpu, FLAG_Z, (result & 0x00FF) == 0);
    cpu_set_flag(cpu, FLAG_V, (result ^ cpu->a) & (result ^ (uint16_t)cpu->fetched ^ 0x00FF) & 0x80);
    cpu_set_flag(cpu, FLAG_N, result & 0x80);

    cpu->a = result & 0x00FF;

    return 1;
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
    cpu->x = cpu->a;

    cpu_set_flag(cpu, FLAG_Z, cpu->x == 0);
    cpu_set_flag(cpu, FLAG_N, cpu->x & 0x80);

    return 0;
}

uint8_t TAY(CPU *cpu)
{
    cpu->y = cpu->a;

    cpu_set_flag(cpu, FLAG_Z, cpu->y == 0);
    cpu_set_flag(cpu, FLAG_N, cpu->y & 0x80);

    return 0;
}

uint8_t TSX(CPU *cpu)
{
    cpu->x = cpu->stkp;

    cpu_set_flag(cpu, FLAG_Z, cpu->x == 0);
    cpu_set_flag(cpu, FLAG_N, cpu->x & 0x80);

    return 0;
}

uint8_t TXA(CPU *cpu)
{
    cpu->a = cpu->x;

    cpu_set_flag(cpu, FLAG_Z, cpu->a == 0);
    cpu_set_flag(cpu, FLAG_N, cpu->a & 0x80);

    return 0;
}

uint8_t TXS(CPU *cpu)
{
    cpu->stkp = cpu->x;

    return 0;
}

uint8_t TYA(CPU *cpu)
{
    cpu->a = cpu->y;

    cpu_set_flag(cpu, FLAG_Z, cpu->a == 0);
    cpu_set_flag(cpu, FLAG_N, cpu->a & 0x80);

    return 0;
}

// illegal ops
uint8_t XXX(CPU *cpu)
{
    return 0;
}
