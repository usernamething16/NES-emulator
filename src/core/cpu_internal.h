#ifndef CPU_INTERNAL_H
#define CPU_INTERNAL_H

#include "cpu.h"

typedef struct instruction {
    const char *name;
    uint8_t (*addrmode)(CPU *cpu);
    uint8_t (*operate)(CPU *cpu); 
    uint8_t cycles;
} instruction;

extern const instruction cpu_lookup[256];

// address modes
uint8_t IMP(CPU *cpu);
uint8_t IMM(CPU *cpu);
uint8_t ZP0(CPU *cpu);
uint8_t ZPX(CPU *cpu);
uint8_t ZPY(CPU *cpu);
uint8_t ABS(CPU *cpu);
uint8_t ABX(CPU *cpu);
uint8_t ABY(CPU *cpu);
uint8_t REL(CPU *cpu);
uint8_t IND(CPU *cpu);
uint8_t IZX(CPU *cpu);
uint8_t IZY(CPU *cpu);

// ops
uint8_t ADC(CPU *cpu);
uint8_t AND(CPU *cpu);
uint8_t ASL(CPU *cpu);
uint8_t BCC(CPU *cpu);
uint8_t BCS(CPU *cpu);
uint8_t BEQ(CPU *cpu);
uint8_t BIT(CPU *cpu);
uint8_t BMI(CPU *cpu);
uint8_t BNE(CPU *cpu);
uint8_t BPL(CPU *cpu);
uint8_t BRK(CPU *cpu);
uint8_t BVC(CPU *cpu);
uint8_t BVS(CPU *cpu);
uint8_t CLC(CPU *cpu);
uint8_t CLD(CPU *cpu);
uint8_t CLI(CPU *cpu);
uint8_t CLV(CPU *cpu);
uint8_t CMP(CPU *cpu);
uint8_t CPX(CPU *cpu);
uint8_t CPY(CPU *cpu);
uint8_t DEC(CPU *cpu);
uint8_t DEX(CPU *cpu);
uint8_t DEY(CPU *cpu);
uint8_t EOR(CPU *cpu);
uint8_t INC(CPU *cpu);
uint8_t INX(CPU *cpu);
uint8_t INY(CPU *cpu);
uint8_t JMP(CPU *cpu);
uint8_t JSR(CPU *cpu);
uint8_t LDA(CPU *cpu);
uint8_t LDX(CPU *cpu);
uint8_t LDY(CPU *cpu);
uint8_t LSR(CPU *cpu);
uint8_t NOP(CPU *cpu);
uint8_t ORA(CPU *cpu);
uint8_t PHA(CPU *cpu);
uint8_t PHP(CPU *cpu);
uint8_t PLA(CPU *cpu);
uint8_t PLP(CPU *cpu);
uint8_t ROL(CPU *cpu);
uint8_t ROR(CPU *cpu);
uint8_t RTI(CPU *cpu);
uint8_t RTS(CPU *cpu);
uint8_t SBC(CPU *cpu);
uint8_t SEC(CPU *cpu);
uint8_t SED(CPU *cpu);
uint8_t SEI(CPU *cpu);
uint8_t STA(CPU *cpu);
uint8_t STX(CPU *cpu);
uint8_t STY(CPU *cpu);
uint8_t TAX(CPU *cpu);
uint8_t TAY(CPU *cpu);
uint8_t TSX(CPU *cpu);
uint8_t TXA(CPU *cpu);
uint8_t TXS(CPU *cpu);
uint8_t TYA(CPU *cpu);

// illegal ops
uint8_t XXX(CPU *cpu);

#endif
