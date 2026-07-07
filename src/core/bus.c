#include "bus.h"

void bus_init(Bus *bus)
{
    cpu_connect_bus(&bus->cpu, bus);
    int size = sizeof(bus->ram)/sizeof(bus->ram[0]);
    for (int i = 0; i < size; i++)
        bus->ram[i] = 0x00;
}

uint8_t bus_read(Bus *bus, uint16_t addr)
{
    if (addr <= 0x1FFF)
        return bus->ram[addr & 0x07FF];
    if (addr >= 0x8000) {
        uint8_t v = cartridge_read(&bus->cart, addr);
        //printf("fetch %04X -> %02X\n", addr, v);
        return v;
    }
    return 0x00;
}

void bus_write(Bus *bus, uint16_t addr, uint8_t data)
{
    if (addr <= 0x1FFF)
        bus->ram[addr & 0x07FF] = data;
    else if (addr >= 0x8000)
        cartridge_write(&bus->cart, addr, data);
}
