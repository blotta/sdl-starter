#include "game_utils.h"
#include <math.h>



// Float
vec2f vec2f_create(float x, float y)
{
    vec2f res = {.x = x, .y = y};
    return res;
}

vec2f vec2f_clone(const vec2f* v)
{
    vec2f res = VEC2F_ZERO;
    vec2f_add(&res, &res, v);
    return res;
}

vec2f* vec2f_add(vec2f* res, const vec2f* a, const vec2f* b)
{
    res->x = a->x + b->x;
    res->y = a->y + b->y;
    return res;
}

vec2f* vec2f_add_i(vec2f* res, const vec2f* v, float i)
{
    res->x = v->x + i;
    res->y = v->y + i;
    return res;
}

vec2f* vec2f_sub(vec2f* res, const vec2f* a, const vec2f* b)
{
    res->x = a->x - b->x;
    res->y = a->y - b->y;
    return res;
}

vec2f* vec2f_sub_i(vec2f* res, const vec2f* v, float i)
{
    res->x = v->x - i;
    res->y = v->y - i;
    return res;
}

vec2f* vec2f_mult(vec2f* res, const vec2f* a, const vec2f* b)
{
    res->x = a->x * b->x;
    res->y = a->y * b->y;
    return res;
}

vec2f* vec2f_mult_i(vec2f* res, const vec2f* v, float i)
{
    res->x = v->x * i;
    res->y = v->y * i;
    return res;
}

float vec2f_magnitude(const vec2f* v)
{
    return sqrtf(v->x * v->x + v->y * v->y);
}

vec2f* vec2f_normalize(vec2f* v)
{
    float mag = vec2f_magnitude(v);
    v->x /= mag;
    v->y /= mag;
    return v;
}

float vec2f_point_angle(vec2f* from, vec2f* to) {
    // return fmod(r2d(atan2(to->y - from->y, to->x - from->x)), 360);
    float res = r2d(atan2(to->y - from->y, to->x - from->x));
    return res < 0 ? res + 360 : res;
}


vec2f* vec2f_rotated(vec2f* res, const vec2f* v, float angle)
{
    float rx = cos(d2r(angle)) * v->x - sin(d2r(angle)) * v->y;
    float ry = sin(d2r(angle)) * v->x + cos(d2r(angle)) * v->y;
    res->x = rx;
    res->y = ry;
    return res;
}
