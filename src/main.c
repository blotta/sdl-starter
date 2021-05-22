#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
#include <time.h>
#include <math.h>

#include "game_utils/game_utils.h"
#include "utils/utils.h"

#include "square.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif


int main(int argc, char *argv[])
{
    srand(time(NULL));

    if( SDL_Init(SDL_INIT_VIDEO) != 0 )
        printf("SDL could not initialize! SDL_Error: %s\n",SDL_GetError());

    SDL_Window* window = SDL_CreateWindow("Hello",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024,720,
        0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED);// |
        // SDL_RENDERER_PRESENTVSYNC);

    // SDL_FRect r = {50.f, 50.f, 100.f, 100.f};

    Square sq;
    square_create(&sq, 50.f, 50.f, 0.f, 100.f, 100.f, 400.f);

    float factor = 100.f;

    // Loop
    int running = 1;
    game_time_init(60, SDL_GetTicks, SDL_Delay, true);
    while(running)
    {
        double delta = game_time_update(true);


        // Events
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        running = 0;
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_UP)
                        factor += 25;
                    if (event.key.keysym.sym == SDLK_DOWN)
                        factor -= 25;
                    if (event.key.keysym.sym == SDLK_RIGHT)
                        factor = fabsf(factor);
                    if (event.key.keysym.sym == SDLK_LEFT)
                        factor = -fabsf(factor);

            }
        }

        // Update
        int mx, my;
        SDL_GetMouseState(&mx, &my);
        vec2f mouse = {mx, my}; 

        vec2f vel = approach(&sq.pos, &mouse, sq.speed * delta, factor, false);

        // printf("pos %f, %f -- factor %f -- speed %f\n",
        //     sq.pos.x, sq.pos.y, factor, vec2f_magnitude(&vel));

        // Render
        SDL_SetRenderDrawColor(renderer, 0, 100, 100, 255);
        SDL_RenderClear(renderer);

        square_draw(&sq, renderer);


        // Swap
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
