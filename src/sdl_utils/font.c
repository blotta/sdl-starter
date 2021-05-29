#include "game_utils.h"
#include "sdl_utils.h"

const int FONT_PRINTABLE_START = 32;

// Create font
void font_create(font_t* out,
    SDL_Renderer* rend, const char** data, uint32_t bytes_per_row, uint32_t rows_per_character, uint32_t length,
    uint8_t red, uint8_t green, uint8_t blue) {

    out->length = length;
    out->bytes_per_row = bytes_per_row;
    out->rows_per_character = rows_per_character;
    out->data = (char*)data;
    out->scale = 1;
    out->rend = rend;
    out->tex = data_to_texture(rend, data, bytes_per_row, rows_per_character, length, red, green, blue);
}

void font_destroy(font_t* font)
{
    SDL_DestroyTexture(font->tex);
}

// draw text
void draw_text(font_t* font, int32_t x, int32_t y, const char* str)
{
    int w = font->bytes_per_row * 8;
    int h = font->rows_per_character;
    uint32_t scale = font->scale;
    SDL_Rect sr = { 0, 0, w, h }; // change y to get a different character
    SDL_Rect dr = { x, y, w * scale, h * scale }; // change x to print a char next to another

    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        char c = str[i];
        int offset = c - FONT_PRINTABLE_START;
        sr.y = h * offset;
        dr.x = x + i * w * scale;
        SDL_RenderCopy(font->rend, font->tex, &sr, &dr);
    }
}
