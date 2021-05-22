#include "game_utils.h"
#include <math.h>


// Float
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