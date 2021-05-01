#include "game_utils.h"

static struct {
    uint32_t before;
    uint8_t target_fps;
    uint32_t (*getMsFunc)();
    void (*delayFunc)(int);
} _gtc;
// static struct __game_time_config _gtc;

void game_time_init(uint8_t target_fps, void* getMsFunc, void* delayFunc, bool first_delay)
{
    _gtc.target_fps = target_fps;
    _gtc.getMsFunc = getMsFunc;
    _gtc.before = _gtc.getMsFunc();

    _gtc.delayFunc = delayFunc;
    if (first_delay)
        _gtc.delayFunc(1000/target_fps);
}

double game_time_update(bool should_delay)
{
    uint32_t now = _gtc.getMsFunc();
    uint32_t diff = now - _gtc.before;
    uint32_t ideal_time =  1000/_gtc.target_fps;
    if (should_delay && diff < ideal_time)
    {
        _gtc.delayFunc(ideal_time - diff);
        now = _gtc.getMsFunc();
        diff = now - _gtc.before;
    }

    _gtc.before = now;
    double delta = ((double)diff) / 1000.0;
    return delta;
}

double game_deltatime()
{
    uint32_t now = _gtc.getMsFunc();
    uint32_t diff = now - _gtc.before;
    return ((double)diff) / 1000.0;
}

uint32_t game_time_msnow()
{
    return _gtc.getMsFunc();
}