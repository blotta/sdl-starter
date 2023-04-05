#include <stdio.h>
#include <SDL2/SDL.h>

#include "main.h"


const char bulletFrames[1][8] = {
    {0x00, 0x00, 0x00, 0x3c, 0x3c, 0x00, 0x00, 0x00}
};

void bullets_init(BulletPool* bullet_pool, uint32_t capacity, SDL_Renderer* rend)
{

    bullet_pool->capacity = capacity;
    bullet_pool->speed = 900.f;

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

    bullet_pool->tex = data_to_texture(rend, (const char**)&bulletFrames, 1, 8, 1, 0xFC, 0xBA, 0x03);
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
                b->rot = vec2f_point_angle(&b->vel, shoot_dir);
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
                bullet_pool->bullets[i].pos.x - 8,
                bullet_pool->bullets[i].pos.y - 8,
                16,
                16};
            SDL_RenderCopyExF(rend, bullet_pool->tex, NULL, &r, bullet_pool->bullets[i].rot, NULL, SDL_FLIP_NONE);
        }
    }
}


void bullets_on_bullet_hit_enemy_event_handler(EventData* edata) {
    BulletHitEnemyEventData* data = (BulletHitEnemyEventData*)edata;
    // printf("bullets handling bullet_hit_enemy event. Enemy:%x Bullet: %x Size: %d %d\n", data->enemy, data->bullet, data->size, sizeof(BulletHitEnemyEventData));
    data->bullet->lifetime = 0;
    data->enemy->health -= 50;
}
