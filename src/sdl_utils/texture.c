#include "sdl_utils.h"
#include "game_utils.h"

SDL_Texture* data_to_texture(
    SDL_Renderer* rend,
    const char** data, uint32_t bytes_per_row, uint32_t row_count, uint32_t elem_count,
    uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t col_count = bytes_per_row * 8;

    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    uint32_t* pixel_data = (uint32_t*)malloc(sizeof(*pixel_data) * col_count * row_count * elem_count);

    for (uint32_t i = 0; i < elem_count; i++)
    {
        uint32_t elem = i * col_count * row_count;
        bits_to_pixels(&pixel_data[elem], (const char*)&data[i], bytes_per_row, row_count, r, g, b);
    }
    // creating a vertical strip surface of the elements
    // pixel_data holds each row of a character continuously, so vstrip is easier to load
    SDL_Surface* surf = SDL_CreateRGBSurfaceFrom(
        (void*)pixel_data,               // 0xRRGGBBAA for each pixel
        col_count,                       // width
        row_count * elem_count,          // height
        32,                              // depth
        col_count * sizeof(*pixel_data), // pitch (length of a row of pixels in bytes)
        rmask, gmask, bmask, amask);     // color mask

    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surf);

    SDL_FreeSurface(surf);
    free(pixel_data);

    return tex;
}