#include <stdio.h>
#include <string.h>

#include "core/bus.h"
#include "core/cartridge.h"
#include "platform/video.h"

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

    Video *video = video_create("nes", 256, 240, 768, 720);

    while (video_poll(video)) {
        do {
            bus_clock(&nes);            
        } while (!nes.ppu.frame_done);
        nes.ppu.frame_done = 0;

        // todo: everything else

        video_present(video, nes.ppu.framebuffer);
    }

    video_destroy(video);
    return 0;
}