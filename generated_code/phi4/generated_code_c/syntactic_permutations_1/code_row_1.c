#include <stddef.h>

void mem_copy(void *dest, const void *src, size_t n) {
    unsigned char *d = dest;
    const unsigned char *s = src;

    for (size_t i = 0; i < n; ++i) {
        d[i] = s[i];
    }
}