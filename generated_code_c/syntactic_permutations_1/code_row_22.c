#include <stddef.h>
    
    void memcpy(void* dest, const void* src, size_t n) {
        char* d = (char*)dest;
        char* s = (char*)src;
        while (n--) *d++ = *s++;
    }