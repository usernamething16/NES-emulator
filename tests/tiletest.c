#include "core/ppu.h"
#include "core/cartridge.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    const char *rom = (argc > 1) ? argv[1] : "tests/roms/nestest.nes";

    Cartridge cart;
    if (cartridge_load(&cart, rom) != 0) {
        fprintf(stderr, "could not load ROM: %s\n", rom);
        return 1;
    }

    PPU ppu;
    ppu_init(&ppu);
    ppu_connect_cartridge(&ppu, &cart);
    
    uint8_t tile[64];
    for (int index = 0; index < 16; index++) {
        printf("TILE %d\n", index);
        ppu_decode_tile(&ppu, 0, index, tile);

        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                putchar(" .o0"[tile[row * 8 + col]]);
            }
            putchar('\n');
        }
    }

    return 0;
}