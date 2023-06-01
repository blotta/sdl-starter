#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define PI 3.14159265358979323846264338327950288

#define r2d(x) x * (180 / PI)
#define d2r(x) x * (PI / 180)

///////////////
// game_time //
///////////////

void game_time_init(uint8_t min_fps, void* getMsFunc, void* delayFunc, bool first_delay);
double game_time_update(bool should_delay);
double game_deltatime();
uint32_t game_time_msnow();
uint16_t game_fps();


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

#define VEC2F_ZERO (vec2f){ .x = 0, .y = 0 }
#define VEC2F_UP (vec2f){ .x = 0, .y = -1 }
#define VEC2F_DOWN (vec2f){ .x = 0, .y = 1 }
#define VEC2F_LEFT (vec2f){ .x = -1, .y = 0 }
#define VEC2F_RIGHT (vec2f){ .x = 1, .y = 0 }

#define VEC2I_ZERO (vec2i){ .x = 0, .y = 0 }
#define VEC2I_UP (vec2i){ .x = 0, .y = -1 }
#define VEC2I_DOWN (vec2i){ .x = 0, .y = 1 }
#define VEC2I_LEFT (vecif){ .x = -1, .y = 0 }
#define VEC2I_RIGHT (vecif){ .x = 1, .y = 0 }

vec2f vec2f_create(float x, float y);
vec2f vec2f_clone(const vec2f* v);

vec2f* vec2f_add(vec2f* res, const vec2f* a, const vec2f* b);
vec2f* vec2f_add_i(vec2f* res, const vec2f* a, float i);

vec2f* vec2f_sub(vec2f* res, const vec2f* a, const vec2f* b);
vec2f* vec2f_sub_i(vec2f* res, const vec2f* a, float i);

vec2f* vec2f_mult(vec2f* res, const vec2f* a, const vec2f* b);
vec2f* vec2f_mult_i(vec2f* res, const vec2f* a, float i);

float vec2f_magnitude(const vec2f* v);
vec2f* vec2f_normalize(vec2f* v);

float vec2f_point_angle(vec2f* from, vec2f* to);

vec2f* vec2f_rotated(vec2f* res, const vec2f* v, float angle);

///////////////
// collision //
///////////////

typedef struct {
    bool hasHit;
    vec2f hit;
} RaycastHitResult;

bool gu_collision_box_box_check(int32_t x1, int32_t y1, int32_t w1, int32_t h1, int32_t x2, int32_t y2, int32_t w2, int32_t h2);

bool gu_collision_box_point_check(int32_t x1, int32_t y1, int32_t w1, int32_t h1, int32_t x2, int32_t y2);

RaycastHitResult gu_castray_point_box(vec2f* from, vec2f* to, int32_t bx, int32_t by, int32_t bw, int32_t bh, uint16_t resolution);

///////////
// Event //
///////////

typedef struct {
    size_t size;
    void* data;
} EventData;

typedef struct {
    void (*handleFunc)(EventData*);
} EventListener;

typedef struct {
    char name[24];
    EventListener listeners[10];
    size_t listeners_length;
} Event;

void gu_event_init();
void gu_event_deinit();

void gu_event_register(const char* name);

void gu_event_subscribe(const char* name, void* handleFunc);

void gu_event_trigger(const char* name, EventData* eventData);

void gu_event_invoke();

//////////
// move //
//////////

vec2f gu_approach(vec2f* pos, const vec2f* to,
                float speed, float factor, bool cap_speed);

float gu_lerp_anglef(float from, float to, float speed);

/////////////
// convert //
/////////////

#ifndef BLT_LITTLE_ENDIAN
#define BLT_LITTLE_ENDIAN 1
#endif

// Maps each 1 bit to a RGBA pixel of a single color, 0 bit to transparent
void bits_to_pixels(
    uint32_t* pixels,
    const char* bits,
    uint32_t bytes_per_row,
    uint32_t row_count,
    uint8_t r, uint8_t g, uint8_t b);

#endif
