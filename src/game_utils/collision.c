#include "game_utils.h"

bool gu_collision_box_box_check(int32_t x1, int32_t y1, int32_t w1, int32_t h1, int32_t x2, int32_t y2, int32_t w2, int32_t h2) {
    return x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && h1 + y1 > y2;
}

bool gu_collision_box_point_check(int32_t x1, int32_t y1, int32_t w1, int32_t h1, int32_t x2, int32_t y2) {
    return x2 > x1 && x2 < x1 + w1 && y2 > y1 && y2 < y1 + h1;
}