#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core/bus.h"
#include "core/cartridge.h"

static int log_field(const char *line, const char *label)
{
    const char *p = strstr(line, label);
    if (!p)
        return -1;
    return (int)strtol(p + strlen(label), NULL, 16);
}

int main(int argc, char **argv)
{
    const char *rom_path = (argc > 1) ? argv[1] : "tests/roms/nestest.nes";
    const char *log_path = (argc > 2) ? argv[2] : "tests/roms/nestest.log";

    Bus nes;
    memset(&nes, 0, sizeof(nes));
    bus_init(&nes);

    if (cartridge_load(&nes.cart, rom_path) != 0) {
        fprintf(stderr, "could not load ROM %s\n", rom_path);
        return 1;
    }

    FILE *log = fopen(log_path, "r");
    if (!log) {
        fprintf(stderr, "could not open log: %s\n", log_path);
        return 1;
    }

    cpu_reset(&nes.cpu);
    nes.cpu.pc = 0xC000;
    nes.cpu.cycles = 0;

    char line[256];
    long n = 0;

    while (fgets(line, sizeof line, log)) {
        n++;

        int e_pc = (int)strtol(line, NULL, 16);
        int e_a = log_field(line, "A:");
        int e_x = log_field(line, "X:");
        int e_y = log_field(line, "Y:");
        int e_p = log_field(line, "P:");
        int e_sp = log_field(line, "SP:");

        if (nes.cpu.pc != e_pc || nes.cpu.a != e_a ||
            nes.cpu.x != e_x || nes.cpu.y != e_y ||
            nes.cpu.status != e_p || nes.cpu.stkp != e_sp) {
            
            printf("MISMATCH at line %ld:\n", n);
            printf(" %s", line);
            printf("  expected  PC:%04X A:%02X X:%02X Y:%02X P:%02X SP:%02X\n",
                   e_pc, e_a, e_x, e_y, e_p, e_sp);
            printf("  got       PC:%04X A:%02X X:%02X Y:%02X P:%02X SP:%02X\n",
                   nes.cpu.pc, nes.cpu.a, nes.cpu.x, nes.cpu.y,
                   nes.cpu.status, nes.cpu.stkp);
            fclose(log);
            return 1;
        }

        do {
            cpu_clock(&nes.cpu);
        } while (!cpu_complete(&nes.cpu));
    }

    printf("PASS: all %ld log lines matched\n", n);
    fclose(log);
    return 0;
}