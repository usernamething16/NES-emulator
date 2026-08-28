#include "platform/video.h"
#include <stdio.h>

int main(void)
{
    // test gradient
    static uint32_t fb[256 * 240];
    Video *v = video_create("testing", 256, 240, 768, 720);
    if (!v) {
        fprintf(stderr, "video init failed\n");
        return 1;
    }
    for (int y = 0; y < 240; y++)
        for (int x = 0; x < 256; x++)
            fb[y * 256 + x] = 0xFF000000 | (x << 16) | (y << 8);
    while (video_poll(v))
        video_present(v, fb);

    video_destroy(v);

    return 0;
}