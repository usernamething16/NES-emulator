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
    return 0;
}

uint8_t BCS(CPU *cpu)
{
    return 0;
}

uint8_t BEQ(CPU *cpu)
{
    return 0;
}

uint8_t BIT(CPU *cpu)
{
    return 0;
}

uint8_t BMI(CPU *cpu)
{
    return 0;
}

uint8_t BNE(CPU *cpu)
{
    return 0;
}

uint8_t BPL(CPU *cpu)
{
    return 0;
}

uint8_t BRK(CPU *cpu)
{
    return 0;
}

uint8_t BVC(CPU *cpu)
{
    return 0;
}


uint8_t BVS(CPU *cpu)
{
    return 0;
}

uint8_t CLC(CPU *cpu)
{
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
    return 0;
}

uint8_t LDA(CPU *cpu)
{
    return 0;
}

uint8_t LDX(CPU *cpu)
{
    return 0;
}

uint8_t LDY(CPU *cpu)
{
    return 0;
}

uint8_t LSR(CPU *cpu)
{
    return 0;
}

uint8_t NOP(CPU *cpu)
{
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
    return 0;
}

uint8_t SBC(CPU *cpu)
{
    return 0;
}

uint8_t SEC(CPU *cpu)
{
    return 0;
}

uint8_t SED(CPU *cpu)
{
    return 0;
}

uint8_t SEI(CPU *cpu)
{
    return 0;
}

uint8_t STA(CPU *cpu)
{
    return 0;
}

uint8_t STX(CPU *cpu)
{
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
