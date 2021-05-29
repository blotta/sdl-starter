#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>


// Maps data to pixels in a SDL_Texture
// @param rend: SDL renderer to use
// @param data: byte array
// @param side_size: size of side of a squared element
// @param elem_count: how many elements
// @param r: red
// @param g: green
// @param b: blue
SDL_Texture* data_to_texture(
    SDL_Renderer* rend,
    const char** data,
    uint32_t bytes_per_row,
    uint32_t row_count,
    uint32_t elem_count,
    uint8_t r, uint8_t g, uint8_t b);




///////////
/* FONT */
///////////

#ifdef SDL_UTILS_FONT_8X8_BASIC
#include "font8x8_basic.h"
#endif

typedef struct font_t {
    uint32_t length;
    uint32_t bytes_per_row;
    uint32_t rows_per_character;
    uint32_t scale;
    SDL_Renderer* rend;
    SDL_Texture* tex;
    char* data;
} font_t;

// Create font
void font_create(font_t* out,
    SDL_Renderer* rend, const char** data, uint32_t bytes_per_row, uint32_t rows_per_character, uint32_t length,
    uint8_t red, uint8_t green, uint8_t blue);

void font_destroy(font_t* font);

// draw text
void draw_text(font_t* font, int32_t x, int32_t y, const char* str);

#endif
