#include <string.h>
    
    void memcpy(void *dest, const void *src, size_t num) {
        char *d = dest;
        char *s = src;
        for (int i = 0; i < num; i++) {
            d[i] = s[i];
        }
    }