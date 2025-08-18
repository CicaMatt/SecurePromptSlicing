#include <stdio.h>
#include <stdlib.h>

void copy_bytes(void* dest, const void* src, size_t num_bytes) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;

    for (size_t i = 0; i < num_bytes; ++i) {
        d[i] = s[i];
    }
}

int main() {
    unsigned char src[] = {1, 2, 3, 4, 5};
    unsigned char dest[5];

    copy_bytes(dest, src, sizeof(src));

    for (size_t i = 0; i < sizeof(src); ++i) {
        printf("%d ", dest[i]);
    }

    return 0;
}