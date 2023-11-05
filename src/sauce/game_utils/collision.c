#include "game_utils.h"

bool gu_collision_box_box_check(int32_t x1, int32_t y1, int32_t w1, int32_t h1, int32_t x2, int32_t y2, int32_t w2, int32_t h2) {
    return x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && h1 + y1 > y2;
}

bool gu_collision_box_point_check(int32_t x1, int32_t y1, int32_t w1, int32_t h1, int32_t x2, int32_t y2) {
    return x2 > x1 && x2 < x1 + w1 && y2 > y1 && y2 < y1 + h1;
}

RaycastHitResult gu_castray_point_box(vec2f* from, vec2f* to, int32_t bx, int32_t by, int32_t bw, int32_t bh, uint16_t resolution) {
    vec2f dir;
    vec2f_sub(&dir, to, from);
    float length = vec2f_magnitude(&dir);

    vec2f_normalize(&dir);
    float each_len = length / resolution;

    vec2f each_dir;

    vec2f currPos = vec2f_create(from->x, from->y);

    for (float len = 0; len <= length; len += each_len) {
        vec2f_mult_i(&each_dir, &dir, len);
        vec2f_add(&currPos, from, &each_dir);

        bool hit = gu_collision_box_point_check(bx, by, bw, bh, currPos.x, currPos.y);
        if (hit) {
            RaycastHitResult res = {
                .hasHit = true,
                .hit = currPos
            };
            return res;
        }

    }

    RaycastHitResult res = {
        .hasHit = false,
    };
    return res;
}