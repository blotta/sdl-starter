#ifndef SNAKE_H
#define SNAKE_H

#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

typedef enum {
    UP = 1, DOWN, LEFT, RIGHT
} Direction;

typedef struct {
    int x, y;
} SnakePart;

typedef struct {
    SnakePart* parts;
    int length, capacity, head_index, tail_index;
    Direction dir;
    bool should_grow;
    bool can_turn;
} Snake;

typedef struct {
    int x, y;
    bool eaten;
} Fruit;

void snake_init(Snake* s, size_t initialCapacity, int hx, int hy);
void snake_deinit(Snake* snake);
SnakePart snake_head_get(Snake* s);
/* void snake_move(Snake* s); */
void snake_move(Snake* s, int xmin, int ymin, int xmax, int ymax);
void snake_handle_dir(Snake* s, SDL_KeyCode key);
bool snake_has_part_at(Snake* s, int x, int y, bool ignoreHead);
void fruit_place(Fruit* f, Snake* s, int xmin, int ymin, int xmax, int ymax);

#endif
