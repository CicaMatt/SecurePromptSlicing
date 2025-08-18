#include <stddef.h>

void memcpy(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    while (n--) {
        *d++ = *s++;
    }
}

int main() {
    char source[] = "Hello, world!";
    char destination[20];

    memcpy(destination, source, sizeof(source));

    return 0;
}