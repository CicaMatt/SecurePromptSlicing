#include <stdlib.h>

void *alloc(size_t size) {
    void *pointer = malloc(size);
    memset(pointer, 0, size);
    return pointer;
}