#ifndef VIDEO_H
#define VIDEO_H

#include <stdint.h>

typedef struct Video Video;

Video *video_create(const char *title, int tex_w, int tex_h, int win_w, int win_h);
void video_destroy(Video *v);
int video_poll(Video *v);
void video_present(Video *v, const uint32_t *frame_buffer);

#endif