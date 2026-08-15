#include "video.h"
#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>

struct Video {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    int tex_w;
    int tex_h;
};

Video *Video_Create(const char *title, int tex_w, int tex_h, int win_w, int win_h)
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Sdl_Init failed");
        return NULL;
    }

    Video *v = calloc(1, sizeof v);
    if (!v) {
        SDL_Quit();
        return NULL;
    }

    v->tex_w = tex_w;
    v->tex_h = tex_h;
}