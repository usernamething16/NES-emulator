#include "bus.h"

void bus_init(Bus *bus)
{

}

uint8_t bus_read(Bus *bus, uint16_t addr)
{
    if (addr >= 0x0000 && addr <= 0xFFFF)
        return bus->ram[addr];
    return 0x00;
}

void bus_write(Bus *bus, uint16_t addr, uint8_t data)
{
    if (addr >= 0x0000 && addr <= 0xFFFF)
        bus->ram[addr] = data;
}