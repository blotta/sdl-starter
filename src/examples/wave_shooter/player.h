#include <SDL2/SDL.h>
#include "game_utils.h"

typedef struct {
    vec2f pos;
    float rot;
    vec2f size;
    float speed;
    SDL_Texture* tex;
} Player;

void player_create(Player* player, float px, float py, float rot, float sx, float sy, float speed, SDL_Renderer* rend)
{
    player->pos.x = px;
    player->pos.y = py;
    player->rot = rot;
    player->size.x = sx;
    player->size.y = sx;
    player->speed = speed;

    Uint32 rmask, gmask, bmask, amask;

    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
    on the endianness (byte order) of the machine */
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

    SDL_Surface* surf = SDL_CreateRGBSurface(0, sx, sy, 32, rmask, gmask, bmask, amask);
    if (surf == NULL) {
        fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_FillRect(surf, NULL, 0xAAAAAAFF);

    player->tex = SDL_CreateTextureFromSurface(rend, surf);

    if (player->tex == NULL) {
        fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_FreeSurface(surf);
}

void player_draw(Player* player, SDL_Renderer* rend)
{
    SDL_FRect r = {player->pos.x - player->size.x/2, player->pos.y - player->size.y/2, player->size.x, player->size.y};
    if(-1 == SDL_RenderCopyExF(rend, player->tex, NULL, &r, player->rot, NULL, SDL_FLIP_NONE)) {
        fprintf(stderr, "SDL_RenderCopyF failed: %s\n", SDL_GetError());
        exit(1);
    }
}

