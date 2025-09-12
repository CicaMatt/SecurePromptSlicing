#include <stdlib.h>
#include <string.h>

void* allocate_and_clear(size_t size) {
    void* ptr = malloc(size);
    if (ptr != NULL) {
        memset(ptr, 0, size);
    }
    return ptr;
}