#include <stdio.h>
#include <stdint.h>

void memcpy_custom(void *dest, const void *src, size_t n) {
    char *d = (char *) dest;
    const char *s = (const char *) src;

    while (n--) {
        *d++ = *s++;
    }
}

int main() {
    char source[] = "Hello, World!";
    char destination[20];

    memcpy_custom(destination, source, sizeof(source));

    printf("Copied string: %s\n", destination);

    return 0;
}