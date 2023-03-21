#include <SDL2/SDL.h>
#include "game_utils.h"

typedef enum {
    IDLE = 0,
    WALKING
} Player_State;

typedef struct {
    vec2f pos;
    float rot;
    vec2f size;
    float speed;
    Player_State state;
    SDL_Texture* tex;
    SDL_Texture* guntex;
} Player;

// generated with Pixel Encoder App https://nifty-elion-abf12b.netlify.app/
#define PLAYER_FRAME_COUNT 1
const char frames[PLAYER_FRAME_COUNT][8] = {
    { 0x00, 0x7e, 0x42, 0x76, 0x76, 0x7e, 0x7e, 0x76 },
};

#define GUN_FRAME_COUNT 1
const char gunframes[GUN_FRAME_COUNT][8] = {
    { 0x00, 0x00, 0x00, 0x07, 0x3f, 0x1e, 0x00, 0x00 }
};

void player_create(Player* player, float px, float py, float rot, float sx, float sy, float speed, SDL_Renderer* rend)
{
    player->pos.x = px;
    player->pos.y = py;
    player->rot = rot;
    player->size.x = sx;
    player->size.y = sx;
    player->speed = speed;
    player->state = IDLE;

    player->tex = data_to_texture(rend, (const char**)&frames, 1, 8, PLAYER_FRAME_COUNT, 0xAA, 0xAA, 0xAA);
    player->guntex = data_to_texture(rend, (const char**)&gunframes, 1, 8, GUN_FRAME_COUNT, 0x33, 0x33, 0x33);
}

void player_draw(Player* player, SDL_Renderer* rend)
{
    Uint8 playerflip = SDL_FLIP_NONE;
    Uint8 gunflip = SDL_FLIP_NONE;
    if (cos(d2r(player->rot)) < 0) {
        playerflip = SDL_FLIP_HORIZONTAL;
        gunflip = SDL_FLIP_VERTICAL;
    }

    float y_offset = 0;
    if (player->state == WALKING) {
        y_offset = 5.f * fabs(cos(0.01f * game_time_msnow()));
    }

    SDL_Rect player_frame = {.x = 0, .y = 0, .w = 8, .h  = 8};

    SDL_FRect player_dest = {player->pos.x - player->size.x/2, -y_offset + player->pos.y - player->size.y/2, player->size.x, player->size.y};
    if(-1 == SDL_RenderCopyExF(rend, player->tex, &player_frame, &player_dest, 0, NULL, playerflip)) {
        fprintf(stderr, "SDL_RenderCopyF failed: %s\n", SDL_GetError());
        exit(1);
    }


    SDL_Rect gun_frame = {.x = 0, .y = 0, .w = 8, .h  = 8};
    SDL_FRect gun_dest = {player->pos.x - player->size.x/2, (-y_offset / 2.f) + player->pos.y - player->size.y/2, player->size.x, player->size.y};
    if(-1 == SDL_RenderCopyExF(rend, player->guntex, &gun_frame, &gun_dest, player->rot, NULL, gunflip)) {
        fprintf(stderr, "SDL_RenderCopyF failed: %s\n", SDL_GetError());
        exit(1);
    }
}


void player_destroy(Player* player)
{
    SDL_DestroyTexture(player->tex);
    SDL_DestroyTexture(player->guntex);
}