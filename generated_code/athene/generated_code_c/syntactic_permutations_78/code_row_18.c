#include <stdlib.h>

void* allocate_and_zero(size_t size) {
    void *ptr = malloc(size);
    if (ptr != NULL) {
        memset(ptr, 0, size);
    }
    return ptr;
}