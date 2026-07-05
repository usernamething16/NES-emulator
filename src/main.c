#include <stdio.h>
#include <string.h>

#include "core/bus.h"
#include "core/cartridge.h"

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <rom.nes>\n", argv[0]);
        return 1;
    }

    Bus nes;
    memset(&nes, 0, sizeof nes);
    bus_init(&nes);

    if (cartridge_load(&nes.cart, argv[1]) != 0) {
        fprintf(stderr, "could not laod ROM: %s", argv[1]);
        return 1;
    }

    cpu_reset(&nes.cpu);

    // placeholder
    for (long i = 0; i < 100000; i++) {
        do {
            cpu_clock(&nes.cpu);
        } while (!cpu_complete(&nes.cpu));
    }
    printf("ran 100000 instructions | PC = $%04X A:%02X X:%02X Y:%02X\n",
            nes.cpu.pc, nes.cpu.a, nes.cpu.x, nes.cpu.y);


    return 0;
}