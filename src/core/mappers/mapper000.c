#include "mapper.h"

int m000_cpu_map_read(Mapper *m, uint16_t addr, uint32_t *mapped)
{
    if (addr >= 0x8000) {
        *mapped = addr & ((m->prg_banks > 1) ? 0x7FFF : 0x3FFF);
        return 1;
    }
    return 0;
}

int m000_cpu_map_write(Mapper *m, uint16_t addr, uint32_t *mapped)
{
    if (addr >= 0x8000) {
        *mapped = addr & ((m->prg_banks > 1) ? 0x7FFF : 0x3FFF);
        return 1;
    }
    return 0;
}

int m000_ppu_map_read(Mapper *m, uint16_t addr, uint32_t *mapped)
{
    (void)m;
    if (addr <= 0x1FFF) {
        *mapped = addr;
        return 1;
    }
    return 0;
}

int m000_ppu_map_write(Mapper *m, uint16_t addr, uint32_t *mapped)
{
    if (addr <= 0x1FFF && m->chr_banks == 0) {
        *mapped = addr;
        return 1;
    }
    return 0;
}

void mapper000_init(Mapper *m, uint8_t prg_banks, uint8_t chr_banks)
{
    m->prg_banks = prg_banks;
    m->chr_banks = chr_banks;
}