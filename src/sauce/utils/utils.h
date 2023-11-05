#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

/////////////
// general //
/////////////

void get_build_str(char* str, size_t size);

////////////////
// file_utils //
////////////////

typedef enum {
    UTIL_FILE_DATA,
    UTIL_FILE_STRING
} util_file_type;

// Returns size of file in bytes
long file_get_size(const char* path);

// Returns pointer to malloc'd contents. Optionally get size of contents in bytes
char* file_allocate_contents(const char* path, util_file_type type, size_t* size);

#endif