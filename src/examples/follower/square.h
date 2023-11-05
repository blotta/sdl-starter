#include <SDL.h>
#include "game_utils.h"

typedef struct {
    vec2f pos;
    float rot;
    vec2f size;
    float speed;
} Square;

void square_create(Square* sq, float px, float py, float rot, float sx, float sy, float speed)
{
    sq->pos.x = px;
    sq->pos.y = py;
    sq->rot = rot;
    sq->size.x = sx;
    sq->size.y = sx;
    sq->speed = speed;
}

void square_draw(Square* sq, SDL_Renderer* rend)
{
    SDL_SetRenderDrawColor(rend, 100, 50, 25, 255);
    SDL_FRect r = {sq->pos.x - sq->size.x/2, sq->pos.y - sq->size.y/2, sq->size.x, sq->size.y};
    SDL_RenderFillRectF(rend, &r);
}