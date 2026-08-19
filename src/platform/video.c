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

Video *video_create(const char *title, int tex_w, int tex_h, int win_w, int win_h)
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

    if (!SDL_CreateWindowAndRenderer(title, win_w, win_h, 0, &v->window, &v->renderer)) {
        fprintf(stderr, "failed to create window and renderer %s\n", SDL_GetError());
        free(v);
        SDL_Quit();
        return NULL;
    }

    v->texture = SDL_CreateTexture(v->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, tex_w, tex_h);

    if (!v->texture) {
        fprintf(stderr, "CreateTexture failed %s\n", SDL_GetError());
        video_destroy(v);
        return NULL;
    }

    SDL_SetTextureScaleMode(v->texture, SDL_SCALEMODE_NEAREST);

    return v;
}

void video_destroy(Video *v)
{

}