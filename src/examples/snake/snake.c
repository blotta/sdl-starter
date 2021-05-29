
#include <stdio.h>

#include "snake.h"

void snake_init(Snake* s, size_t initialCapacity, int hx, int hy)
{
    s->capacity = initialCapacity;
    s->parts = malloc(initialCapacity * sizeof(SnakePart));

    // add parts, head, tail
    s->dir = RIGHT;
    s->length = 3;
    SnakePart h = { hx, hy };
    SnakePart m = { hx, hy + 1 };
    SnakePart t = { hx, hy + 2 };
    s->parts[0] = h;
    s->parts[1] = m;
    s->parts[2] = t;

    s->head_index = 0;
    s->tail_index = 2;

    s->can_turn = true;
    s->should_grow = false;
}

void snake_deinit(Snake* snake)
{
    free(snake->parts);
}

SnakePart snake_head_get(Snake* s)
{
    return s->parts[s->head_index];
}

void snake_move(Snake* s, int xmin, int ymin, int xmax, int ymax)
{
    SnakePart newHead;
    // newHead.x = s->parts[s->head_index].x;
    // newHead.y = s->parts[s->head_index].y;
    newHead = s->parts[s->head_index];

    switch (s->dir)
    {
    case UP: newHead.y -= 1; break;
    case DOWN: newHead.y += 1; break;
    case RIGHT: newHead.x += 1; break;
    case LEFT: newHead.x -= 1; break;
    }

    if (newHead.x < xmin) newHead.x = xmax;
    if (newHead.x > xmax) newHead.x = xmin;
    if (newHead.y < ymin) newHead.y = ymax;
    if (newHead.y > ymax) newHead.y = ymin;

    if (s->should_grow)
    {
        printf("Growing\n");
		if (s->length == s->capacity)
		{
			s->capacity *= 2;
			s->parts = realloc(s->parts, s->capacity * sizeof(SnakePart));
            printf("Reallocated Dyn array to %d cap\n", s->capacity);
		}

        SnakePart n = s->parts[s->head_index];
        s->parts[s->length] = n;
        s->length += 1;

        s->should_grow = false;
    }

	int new_tail_index = s->tail_index < 1 ? s->length - 1 : s->tail_index - 1;
	s->head_index = s->tail_index;
	s->parts[s->head_index].x = newHead.x;
	s->parts[s->head_index].y = newHead.y;
	s->tail_index = new_tail_index;

    s->can_turn = true;
}

void snake_handle_dir(Snake* s, SDL_KeyCode key)
{
    if (!s->can_turn)
        return;

    Direction currDir = s->dir;

    bool isSnakeVertical = s->dir == UP || s->dir == DOWN;
    bool isKeyVertical = key == SDLK_UP || key == SDLK_DOWN;
    bool isKeyHorizontal = key == SDLK_RIGHT || key == SDLK_LEFT;

    Direction keyDir;
    switch (key)
    {
    case SDLK_UP: keyDir = UP; break;
    case SDLK_DOWN: keyDir = DOWN; break;
    case SDLK_LEFT: keyDir = LEFT; break;
    case SDLK_RIGHT: keyDir = RIGHT; break;
    default: break;
    }

    if ((isSnakeVertical && isKeyHorizontal) || (!isSnakeVertical && isKeyVertical))
    {
        s->dir = keyDir;
        s->can_turn = false;
    }

    printf("oldDir: %d ; newDir: %d Got key %s\n", currDir, s->dir, SDL_GetKeyName(key));
}

bool snake_has_part_at(Snake* s, int x, int y, bool ignoreHead)
{
    for (int i = 0; i < s->length; i++)
    {
        if (s->parts[i].x == x && s->parts[i].y == y)
        {
            if (ignoreHead && s->head_index == i)
                continue;
            return true;
        }
    }
    return false;
}

void fruit_place(Fruit* f, Snake* s, int xmin, int ymin, int xmax, int ymax)
{
    int newX, newY;

    do
    {
		newX = xmin + rand() % xmax;
		newY = ymin + rand() % ymax;
    } while (snake_has_part_at(s, newX, newY, false));

    f->x = newX;
    f->y = newY;
    f->eaten = false;
}
