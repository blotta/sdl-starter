#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
// #include <SDL2/SDL_image.h>
#include <time.h>
#include <math.h>

#include "utils.h"
#include "game_utils.h"

#define SDL_UTILS_FONT_8X8_BASIC
#include "sdl_sauce.h"

#include "snake.h"

enum GameState {
    START,
    MENU,
    GAME,
    END
};

int main(int argc, char *argv[])
{
	const int CELL_SIZE = 24;
    const int GRID_SIZE = 25;
	const int WIDTH = (2 + GRID_SIZE) * CELL_SIZE;
	const int HEIGHT = (2 + GRID_SIZE) * CELL_SIZE;

    if( SDL_Init(SDL_INIT_VIDEO) != 0 )
        printf("SDL could not initialize! SDL_Error: %s\n",SDL_GetError());

    char title[128];
    get_build_str(title, 128);
    SDL_Window* window = SDL_CreateWindow(title,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          WIDTH, HEIGHT,
                                          0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    font_t font88;
    font_create(&font88, renderer, (const char**)FONT_8X8_BASIC, 1, 8,
            FONT_8X8_BASIC_LENGTH, 0x00, 0x00, 0x00);

    // Game init
    srand(time(NULL));

    enum GameState gameState = START;

    int score = 0;

    const int wall_w = CELL_SIZE;
    SDL_Rect walls[4] = {
        {0, 0, wall_w, HEIGHT}, // left
        {WIDTH - wall_w, 0, wall_w, HEIGHT}, // right
        {wall_w, 0, WIDTH - 2 * wall_w, wall_w}, // top
        {wall_w, HEIGHT - wall_w, WIDTH - 2 * wall_w, wall_w}, // bottom
    };

    Snake snake;
    snake_init(&snake, 5, 10, 10);

    Fruit fruit;
    fruit.eaten = true;

    const double moveTimerTotal = 0.1;
    double moveTimer = moveTimerTotal;

    // Loop
    int running = 1;
    game_time_init(60, SDL_GetTicks, SDL_Delay, true);
    while(running)
    {
        double delta = game_time_update(true);

        if (gameState == START) {
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
                        switch (event.key.keysym.sym)
                        {
                            case SDLK_ESCAPE:
                                running = 0;
                                break;
                            case SDLK_RETURN:
                                gameState = GAME;
                                break;
                        }
                    default:
                        break;
                }
            }

            // Render
            SDL_SetRenderDrawColor(renderer, 0x3c, 0x3c, 0x3c, 0xff);
            SDL_RenderClear(renderer);

            // Draw walls
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderFillRects(renderer, walls, 4);

            // Draw
            draw_text(&font88, CELL_SIZE, 10, "PRESS ENTER TO START");

            // Swap
            SDL_RenderPresent(renderer);

        } else if (gameState == GAME) {
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
                        switch (event.key.keysym.sym)
                        {
                            case SDLK_ESCAPE:
                                running = 0;
                                break;
                            case SDLK_UP:
                            case SDLK_DOWN:
                            case SDLK_RIGHT:
                            case SDLK_LEFT:
                                snake_handle_dir(&snake, event.key.keysym.sym);
                                break;
                        }
                    default:
                        break;
                }
            }

            // Update
            moveTimer -= delta;
            if (moveTimer <= 0.0) {
                moveTimer = moveTimerTotal;

                if (fruit.eaten) {
                    fruit_place(&fruit, &snake, 1, 1, GRID_SIZE, GRID_SIZE);
                }

                snake_move(&snake, 1, 1, GRID_SIZE, GRID_SIZE);

                if (snake_has_part_at(&snake,
                                      snake.parts[snake.head_index].x,
                                      snake.parts[snake.head_index].y,
                                      true))
                {
                    // eat itself
                    gameState = END;
                }

                if (!fruit.eaten
                        && snake.parts[snake.head_index].x == fruit.x
                        && snake.parts[snake.head_index].y == fruit.y)
                {
                    score++;
                    fruit.eaten = true;
                    snake.should_grow = true;
                }
            }

            // Render
            SDL_SetRenderDrawColor(renderer, 0x3c, 0x3c, 0x3c, 0xff);
            SDL_RenderClear(renderer);

            // Draw walls
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderFillRects(renderer, walls, 4);

            // Draw fruit
            if (!fruit.eaten) {
                SDL_SetRenderDrawColor(renderer, 0xAA, 0x55, 0x55, 0xFF);
                SDL_Rect r = { fruit.x * CELL_SIZE, fruit.y * CELL_SIZE, CELL_SIZE, CELL_SIZE };
                SDL_RenderFillRect(renderer, &r);
            }

            // Draw Snake
            for (int i = 0; i < snake.length; i++) {
                SnakePart part = snake.parts[i];
                SDL_Rect r = { part.x * CELL_SIZE, part.y * CELL_SIZE, CELL_SIZE, CELL_SIZE };
                SDL_SetRenderDrawColor(renderer, 0x55, snake.head_index == i ? 0xAA : 0x99, 0x55, 0xFF);
                SDL_RenderFillRect(renderer, &r);
            }

            // Draw ui
            char scoreMessage[80];
            sprintf_s(scoreMessage, 80, "SCORE: %d", score);
            draw_text(&font88, CELL_SIZE, 10, scoreMessage);

            // Swap
            SDL_RenderPresent(renderer);
        } else if (gameState == END) {
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
                        switch (event.key.keysym.sym)
                        {
                            case SDLK_ESCAPE:
                                running = 0;
                                break;
                            case SDLK_RETURN:
                                score = 0;
                                snake_deinit(&snake);
                                snake_init(&snake, 5, 10, 10);
                                fruit.eaten = true;
                                gameState = START;
                                break;
                        }
                    default:
                        break;
                }
            }

            // Render
            SDL_SetRenderDrawColor(renderer, 0x3c, 0x3c, 0x3c, 0xff);
            SDL_RenderClear(renderer);

            // Draw walls
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderFillRects(renderer, walls, 4);

            // Draw ui
            char scoreMessage[80];
            sprintf_s(scoreMessage, 80, "FINAL SCORE: %d", score);
            draw_text(&font88, CELL_SIZE, 10, scoreMessage);

            font88.scale = 3;
            draw_text(&font88, -(3 * (int)(8 * 4.5f)) + WIDTH / 2, -(3 * 4) + HEIGHT / 2, "GAME OVER");
            font88.scale = 1;

            // Swap
            SDL_RenderPresent(renderer);

        }
    }

    snake_deinit(&snake);

    font_destroy(&font88);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
