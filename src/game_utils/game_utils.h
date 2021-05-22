#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include <stdint.h>
#include <stdbool.h>

///////////////
// game_time //
///////////////

void game_time_init(uint8_t min_fps, void* getMsFunc, void* delayFunc, bool first_delay);
double game_time_update(bool should_delay);
double game_deltatime();
uint32_t game_time_msnow();


/////////
// vec //
/////////

typedef struct {
    float x;
    float y;
} vec2f;

typedef struct {
    int x;
    int y;
} vec2i;

vec2f* vec2f_add(vec2f* res, const vec2f* a, const vec2f* b);
vec2f* vec2f_add_i(vec2f* res, const vec2f* a, float i);

vec2f* vec2f_sub(vec2f* res, const vec2f* a, const vec2f* b);
vec2f* vec2f_sub_i(vec2f* res, const vec2f* a, float i);

vec2f* vec2f_mult(vec2f* res, const vec2f* a, const vec2f* b);
vec2f* vec2f_mult_i(vec2f* res, const vec2f* a, float i);

float vec2f_magnitude(const vec2f* v);
vec2f* vec2f_normalize(vec2f* v);


//////////
// move //
//////////

vec2f approach(vec2f* pos, const vec2f* to,
                float speed, float factor, bool cap_speed);
#endif