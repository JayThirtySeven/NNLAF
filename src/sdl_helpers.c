#include "sdl_helpers.h"

SDL_Surface *create_surface(int32_t w, int32_t h){
    return SDL_CreateRGBSurface(0,w,h,32,0x00FF0000,0x0000FF00,0x000000FF,0xFF000000);
}

SDL_Surface *convert_surface(SDL_Surface *src){
    return SDL_ConvertSurfaceFormat(src, SDL_PIXELFORMAT_ARGB8888, 0);
}

SDL_Surface *load_image(const char *fn){
    SDL_Surface *tmp, *final;
    tmp = IMG_Load(fn);
    final = convert_surface(tmp);
    SDL_FreeSurface(tmp);
    return final;
}

SDL_Texture *create_texture(SDL_Renderer *render, int32_t w, int32_t h){
    return SDL_CreateTexture(render, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, w, h);
}

SDL_Texture *create_streaming_texture(SDL_Renderer *render, int32_t w, int32_t h){
    return SDL_CreateTexture(render, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, w, h);
}

