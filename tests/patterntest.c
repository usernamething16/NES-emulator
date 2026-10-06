#include "platform/video.h"
#include "core/ppu.h"
#include "core/cartridge.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    const uint32_t grayscale[] = {
        0xFF000000,
        0xFF555555,
        0xFFAAAAAA,
        0xFFFFFFFF
    };
    const char *rom = (argc > 1) ? argv[1] : "tests/roms/nestest.nes";

    Cartridge cart;
    if (cartridge_load(&cart, rom) != 0) {
        fprintf(stderr, "could not load ROM: %s\n", rom);
        return 1;
    }

    PPU ppu;
    ppu_init(&ppu);
    ppu_connect_cartridge(&ppu, &cart);

    static uint32_t framebuffer[256 * 128];
    uint8_t tile[64];
    for (int table = 0; table < 2; table++) {
        for (int index = 0; index < 256; index++) {
            ppu_decode_tile(&ppu, table, index, tile);

            int tile_x = index % 16;
            int tile_y = index / 16;

            for (int row = 0; row < 8; row++) {
                for (int col = 0; col < 8; col++) {
                    uint32_t color = grayscale[tile[row * 8 + col]];

                    int px = table * 128 + tile_x * 8 + col; 
                    int py = tile_y * 8 + row;

                    framebuffer[py * 256 + px] = color;
                }
            }
        }
    }

    Video *v = video_create("testing", 256, 128, 512, 256);
    
    if (!v) {
        fprintf(stderr, "video init failed\n");
        return 1;
    }
    while (video_poll(v))
        video_present(v, framebuffer);

    video_destroy(v);

    return 0;
}