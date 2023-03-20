#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
#include <time.h>
#include <math.h>

#include "utils.h"
#include "game_utils.h"

#define SDL_UTILS_FONT_8X8_BASIC
#include "sdl_utils.h"

#include "player.h"
#include "bullet.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));

    if( SDL_Init(SDL_INIT_EVERYTHING) != 0 )
        printf("SDL could not initialize! SDL_Error: %s\n",SDL_GetError());

    char title[128];
    get_build_str(title, 128);
    SDL_Window* window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024,720,
        0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED);

    Player player;
    player_create(&player, 50.f, 50.f, 20.f, 32.f, 32.f, 100.f, renderer);
    vec2f player_direction;
    // vec2f player_velocity;

    BulletPool bullet_pool;
    bullets_init(&bullet_pool, 10, renderer);

    font_t font88;
    font_create(&font88, renderer, (const char**)FONT_8X8_BASIC, 1, 8, FONT_8X8_BASIC_LENGTH, 0xff, 0xff, 0xff);


    // sdl input map
    sdlu_input_mapper_init(5);
    sdlu_input_mapper_track(SDLK_w);
    sdlu_input_mapper_track(SDLK_a);
    sdlu_input_mapper_track(SDLK_s);
    sdlu_input_mapper_track(SDLK_d);
    sdlu_input_mapper_track(SDLK_SPACE);

    // Loop
    int running = 1;
    game_time_init(60, SDL_GetTicks, SDL_Delay, true);
    while(running)
    {
        double delta = game_time_update(true);

        sdlu_pollevents();
        running = !sdlu_input_requested_quit();

        // Update
        vec2i mouse; 
        SDL_GetMouseState(&mouse.x, &mouse.y);


        player_direction = VEC2F_ZERO;
        if (sdlu_input_key_pressed(SDLK_w))
            vec2f_add(&player_direction, &player_direction, &VEC2F_UP);
        if (sdlu_input_key_pressed(SDLK_s))
            vec2f_add(&player_direction, &player_direction, &VEC2F_DOWN);
        if (sdlu_input_key_pressed(SDLK_d))
            vec2f_add(&player_direction, &player_direction, &VEC2F_RIGHT);
        if (sdlu_input_key_pressed(SDLK_a))
            vec2f_add(&player_direction, &player_direction, &VEC2F_LEFT);
        
        if (player_direction.x != 0 && player_direction.y != 0)
            vec2f_normalize(&player_direction);

        vec2f vel = VEC2F_ZERO;
        vec2f_mult_i(&vel, &player_direction, player.speed);

        player.pos.x += vel.x * delta;
        player.pos.y += vel.y * delta;

        float desired_rot = vec2f_point_angle(&player.pos, &(vec2f) {.x = mouse.x, .y = mouse.y});
        // player.rot = desired_rot;
        player.rot = gu_lerp_anglef(player.rot, desired_rot, 1.5 * 360 * delta);

        vec2f bullet_spawn = vec2f_create(20.f, 0);
        vec2f_rotated(&bullet_spawn, &bullet_spawn, player.rot);
        vec2f_add(&bullet_spawn, &bullet_spawn, &player.pos);

        vec2f* shoot_dir_ptr = NULL;
        vec2f shoot_dir = (vec2f){.x = cos(d2r(player.rot)), .y = sin(d2r(player.rot))};
        vec2f_normalize(&shoot_dir);
        if (sdlu_input_mouse_justpressed(SDL_BUTTON_LEFT)) {
            shoot_dir_ptr = &shoot_dir;
            // printf("%f, %f\n", bullet_spawn.x, bullet_spawn.y);
        }

        bullets_update(&bullet_pool, &bullet_spawn, shoot_dir_ptr, delta);

        // Render
        SDL_SetRenderDrawColor(renderer, 0, 100, 100, 255);
        SDL_RenderClear(renderer);

        player_draw(&player, renderer);
        bullets_draw(&bullet_pool, renderer);

        SDL_FRect bsr = {
            .x = bullet_spawn.x,
            .y = bullet_spawn.y,
            .w = 2,
            .h = 2
        };
        SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
        SDL_RenderFillRectF(renderer, &bsr);

        char msg_buff[64];
        sprintf_s(msg_buff, 64, "X: %.2f Y: %.2f ROT: %.2f DESROT: %.2f", player.pos.x, player.pos.y, player.rot, desired_rot);
        draw_text(&font88, 10, 10, msg_buff);
        sprintf_s(msg_buff, 64, "FPS: %d", game_fps());
        draw_text(&font88, 10, 20, msg_buff);

        // Swap
        SDL_RenderPresent(renderer);
    }

    bullets_deinit(&bullet_pool);
    font_destroy(&font88);
    sdlu_input_mapper_deinit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}