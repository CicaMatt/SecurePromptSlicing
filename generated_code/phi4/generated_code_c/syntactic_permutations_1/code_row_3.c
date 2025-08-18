#include <stddef.h>

void memcpy(void *dest, const void *src, size_t n) {
    char *d = (char *)dest;
    const char *s = (const char *)src;

    while (n--) {
        *d++ = *s++;
    }
}

int main() {
    char source[] = "Hello, World!";
    char destination[20];

    memcpy(destination, source, sizeof(source));

    // Use the copied data in destination
    return 0;
}