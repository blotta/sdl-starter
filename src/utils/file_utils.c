#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

long file_get_size(const char* path) {
    printf("Opening %s\n", path);
    FILE* file = fopen(path, "rb");
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);
    return size;
}

char* file_allocate_contents(const char* path, util_file_type type, size_t* size) {
    FILE* file = fopen(path, "rb");
    char* buffer;

    size_t fsize;
    if (!file) {
        printf("Could not open file '%s'\n", path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    size_t alloc_size = type == UTIL_FILE_STRING ? fsize + 1 : fsize;
    // TODO: get allocator as parameter
    buffer = malloc(alloc_size);
    if (!buffer) {
        printf("Could not allocate memory\n");
        return NULL;
    }

    fread(buffer, 1, fsize, file);

    if (type == UTIL_FILE_STRING)
        buffer[fsize] = 0; // null terminated string

    fclose(file);

    if (size)
        *size = fsize; // same if data or string

    if (buffer)
        return buffer;
    
    return NULL;
}