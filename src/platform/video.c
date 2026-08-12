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