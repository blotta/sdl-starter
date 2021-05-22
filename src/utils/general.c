#include <stdio.h>
#include "utils.h"

#ifdef DEBUG
#define BUILD_TARGET "Debug"
#else
#define BUILD_TARGET "Release"
#endif

#ifndef VERSION
#define VERSION "0.0"
#endif

void get_build_str(char* str, size_t size) {
    sprintf_s(str, size, "%s v%s", BUILD_TARGET, VERSION);
}