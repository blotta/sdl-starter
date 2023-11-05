#include <math.h>
#include "game_utils.h"

vec2f gu_approach(vec2f* pos, const vec2f* to,
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


float gu_lerp_anglef(float from, float to, float speed) {
    // assuming deg
    float rFrom = d2r(from);
    float rTo = d2r(to);
    float rSpeed = d2r(speed);
    // float rSpeed = speed;// d2r(speed);

    float c = (1 - rSpeed) * cos(rFrom) + rSpeed * cos(rTo);
    float s = (1 - rSpeed) * sin(rFrom) + rSpeed * sin(rTo);

    float res = r2d(atan2(s, c));
    // return fmod(360 - r2d(atan2f(s, c)), 360);
    // return fmod(360 - r2d(atan2(to->y - from->y, to->x - from->x)), 360);

    return res < 0 ? res + 360 : res;
}
