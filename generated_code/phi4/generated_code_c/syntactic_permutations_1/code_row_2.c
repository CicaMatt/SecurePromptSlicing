#include <stddef.h>

void mem_copy(void *dest, const void *src, size_t n) {
    unsigned char *d = dest;
    const unsigned char *s = src;

    while (n--) {
        *d++ = *s++;
    }
}

int main() {
    unsigned char source[] = {1, 2, 3, 4, 5};
    unsigned char destination[5];

    mem_copy(destination, source, sizeof(source));

    for (size_t i = 0; i < sizeof(source); ++i) {
        printf("%d ", destination[i]);
    }

    return 0;
}