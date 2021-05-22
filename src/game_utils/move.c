#include "game_utils.h"

vec2f approach(vec2f* pos, const vec2f* to,
                float speed, float factor, bool cap_speed)
{
    vec2f dir;
    vec2f_sub(&dir, to, pos);
    float dist = vec2f_magnitude(&dir);
    vec2f_normalize(&dir);

    float f = factor == 0 ? dist : factor;
    float adjusted_speed = (dist/f) * speed;
    if (cap_speed && adjusted_speed > speed)
        adjusted_speed = speed;

    vec2f vel;
    vec2f_mult_i(&vel, &dir, adjusted_speed);

    vec2f_add(pos, pos, &vel);

    return vel;
}