#include <stdio.h>
#include <SDL2/SDL.h>
#include "game_utils.h"

typedef struct {
    vec2f pos;
    vec2f vel;
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

void bullets_init(BulletPool* bullet_pool, uint32_t capacity, SDL_Renderer* rend)
{

    bullet_pool->capacity = capacity;
    bullet_pool->speed = 1000.f;

    bullet_pool->bullet_lifetime = 1.f;

    bullet_pool->bullets = (Bullet*)malloc(capacity * sizeof(Bullet));
    for (size_t i = 0; i < bullet_pool->capacity; i++) {
        Bullet bullet = {
            .pos = VEC2F_ZERO,
            .vel = VEC2F_ZERO,
            .lifetime = 0
        };
        bullet_pool->bullets[i] = bullet;
    }


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

    SDL_Surface* surf = SDL_CreateRGBSurface(0, 5, 5, 32, rmask, gmask, bmask, amask);
    if (surf == NULL) {
        fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_FillRect(surf, NULL, 0xBBBBBBFF);

    bullet_pool->tex = SDL_CreateTextureFromSurface(rend, surf);

    if (bullet_pool->tex == NULL) {
        fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_FreeSurface(surf);
}

void bullets_deinit(BulletPool* bullet_pool) {
    free(bullet_pool->bullets);
}

void bullets_update(BulletPool* bullet_pool, vec2f* origin, vec2f* shoot_dir, float delta) {
    // check shoot
    bool handled_shoot = false;

    // update each bullet
    for (size_t i = 0; i < bullet_pool->capacity; i++) {
        Bullet* b = &bullet_pool->bullets[i];

        if (b->lifetime > 0) {

            vec2f v = VEC2F_ZERO;
            vec2f_add(&v, &v, &b->vel);
            vec2f_mult_i(&v, &v, delta);

            vec2f_add(&b->pos, &b->pos, &v);

            // check collision... blah blah
        } else {
            if (!handled_shoot && shoot_dir != NULL) {
                // printf("Shooting!\n");
                b->pos = (vec2f){.x = origin->x, .y = origin->y};
                b->vel = VEC2F_ZERO;
                vec2f_add(&b->vel, &b->vel, shoot_dir);
                vec2f_normalize(&b->vel);
                vec2f_mult_i(&b->vel, &b->vel, bullet_pool->speed);
                b->lifetime = bullet_pool->bullet_lifetime;
            } else {
                b->pos = VEC2F_ZERO;
                b->vel = VEC2F_ZERO;
                b->lifetime = 0;
            }
            handled_shoot = true;
        }


        b->lifetime -= delta;
    }
}

void bullets_draw(BulletPool* bullet_pool, SDL_Renderer* rend)
{
    for (size_t i = 0; i < bullet_pool->capacity; i++) {
        if (bullet_pool->bullets[i].lifetime > 0) {
            SDL_FRect r = {
                bullet_pool->bullets[i].pos.x,
                bullet_pool->bullets[i].pos.y,
                5,
                5};
            SDL_RenderCopyF(rend, bullet_pool->tex, NULL, &r);

            // SDL_RenderDrawPointF(rend, bullet_pool->bullets[i].pos.x, bullet_pool->bullets[i].pos.y);

        }
    }
}

