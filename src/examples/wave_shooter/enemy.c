#include <SDL.h>
#include "game_utils.h"

#include "main.h"

#define ENEMY_FRAME_COUNT 2
const char enemyframes[ENEMY_FRAME_COUNT][8] = {
    {0x3c, 0x6a, 0x7e, 0x7e, 0x6a, 0x54, 0x7e, 0x76},
    {0x18, 0x7e, 0x6a, 0x7e, 0x7e, 0x7c, 0x7e, 0x76}, 
};

void enemy_create(Enemy* enemy, float px, float py, float rot, float sx, float sy, float speed, SDL_Renderer* rend)
{
    enemy->pos.x = px;
    enemy->pos.y = py;
    // enemy->rot = rot;
    enemy->size.x = sx;
    enemy->size.y = sx;
    enemy->speed = speed;

    enemy->frames_per_sec = 3.f;
    enemy->frame_timer = 1.f / enemy->frames_per_sec;
    enemy->frame_index = 0;
    enemy->frame_count = ENEMY_FRAME_COUNT;

    enemy->health = 100;

    enemy->tex = data_to_texture(rend, (const char**)&enemyframes, 1, 8, ENEMY_FRAME_COUNT, 0x22, 0x22, 0x22);
}

void enemy_destroy(Enemy* enemy)
{
    SDL_DestroyTexture(enemy->tex);
}

void enemy_update(Enemy* enemy, const vec2f* destination, float delta)
{
    vec2f_sub(&enemy->dir, destination, &enemy->pos);
    vec2f_normalize(&enemy->dir);
    vec2f vel = VEC2F_ZERO;
    vec2f_mult_i(&vel, &enemy->dir, enemy->speed * delta);
    vec2f_add(&enemy->pos, &enemy->pos, &vel);

    enemy->frame_timer -= delta;
    if (enemy->frame_timer <= 0) {
        enemy->frame_timer = 1.f / enemy->frames_per_sec;
        enemy->frame_index += 1;
        enemy->frame_index %= enemy->frame_count;
    }
}

void enemy_draw(Enemy* enemy, SDL_Renderer* rend)
{
    Uint8 enemyflip = SDL_FLIP_NONE;
    if (enemy->dir.x < 0) {
        enemyflip = SDL_FLIP_HORIZONTAL;
    }

    SDL_Rect enemy_frame = {.x = 0, .y = 8 * enemy->frame_index, .w = 8, .h  = 8};
    SDL_FRect enemy_dest = {
        enemy->pos.x - enemy->size.x/2,
        enemy->pos.y - enemy->size.y/2,
        enemy->size.x,
        enemy->size.y
    };
    if(-1 == SDL_RenderCopyExF(rend, enemy->tex, &enemy_frame, &enemy_dest, 0, NULL, enemyflip)) {
        printf("SDL_RenderCopyF failed: %s\n", SDL_GetError());
        exit(1);
    }
}


void enemy_on_enemy_hit_player_event_handler(EventData* edata) {
    EnemyHitPlayerEventData* data = (EnemyHitPlayerEventData*)edata;
    
    printf("Enemy attacked event!\n");
    player_take_damage(data->player, 5);
}