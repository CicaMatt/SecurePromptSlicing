#include <stddef.h>

void memcopy(void *dest, const void *src, size_t n) {
    unsigned char *d = dest;
    const unsigned char *s = src;

    while (n--) {
        *d++ = *s++;
    }
}

int main() {
    char source[] = "The quick brown fox jumps over the lazy dog";
    char destination[50];

    memcopy(destination, source, sizeof(source));

    return 0;
}