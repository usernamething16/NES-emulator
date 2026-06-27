#ifndef BUS_H
#define BUS_H

#include <stdint.h>
#include "cpu.h"

typedef struct Bus {
    CPU cpu;
    uint8_t ram[64 * 1024];
} Bus;

void bus_init(Bus *bus);
uint8_t bus_read(Bus *bus, uint16_t addr);
void bus_write(Bus *bus, uint16_t addr, uint8_t data);

#endif