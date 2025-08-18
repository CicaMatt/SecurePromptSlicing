#include <stdio.h>

void mem_copy(void *dest, const void *src, size_t num) {
    char *d = (char *)dest;
    const char *s = (const char *)src;
    for (size_t i = 0; i < num; ++i) {
        d[i] = s[i];
    }
}