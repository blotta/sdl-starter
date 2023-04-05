#pragma once

#include "math.h"
#include "SDL2/SDL.h"
#include "game_utils.h"
#include "sdl_utils.h"

// PLAYER
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

void player_create(Player* player, float px, float py, float rot, float sx, float sy, float speed, SDL_Renderer* rend);
void player_draw(Player* player, SDL_Renderer* rend);
void player_destroy(Player* player);


// BULLETS
typedef struct {
    vec2f pos;
    vec2f vel;
    float rot;
    float lifetime;
} Bullet;

typedef struct {
    Bullet* bullets;
    uint32_t capacity;
    float bullet_lifetime;
    float speed;
    vec2f origin;
    SDL_Texture* tex;
} BulletPool;


void bullets_init(BulletPool* bullet_pool, uint32_t capacity, SDL_Renderer* rend);
void bullets_deinit(BulletPool* bullet_pool);
void bullets_update(BulletPool* bullet_pool, vec2f* origin, vec2f* shoot_dir, float delta);
void bullets_draw(BulletPool* bullet_pool, SDL_Renderer* rend);
void bullets_on_bullet_hit_enemy_event_handler(EventData* edata);

// Enemy
typedef struct {
    vec2f pos;
    vec2f dir;
    vec2f size;
    float speed;
    SDL_Texture* tex;
    float frame_timer;
    float frames_per_sec;
    uint8_t frame_index;
    uint8_t frame_count;
    uint32_t health;
} Enemy;

void enemy_create(Enemy* enemy, float px, float py, float rot, float sx, float sy, float speed, SDL_Renderer* rend);

void enemy_destroy(Enemy* enemy);
void enemy_update(Enemy* enemy, const vec2f* destination, float delta);
void enemy_draw(Enemy* enemy, SDL_Renderer* rend);



// EVENTS
typedef struct {
    size_t size;
    Enemy* enemy;
    Bullet* bullet;
} BulletHitEnemyEventData;
