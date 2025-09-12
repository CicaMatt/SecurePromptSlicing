#include <stddef.h>

void memcpy(void *dest, const void *src, size_t num_bytes) {
    unsigned char *d = (unsigned char *) dest;
    const unsigned char *s = (const unsigned char *) src;

    for (size_t i = 0; i < num_bytes; ++i) {
        d[i] = s[i];
    }
}

#include <stdio.h>

int main() {
    char source[] = "Hello, World!";
    char destination[20];

    memcpy(destination, source, sizeof(source));

    printf("Copied string: %s\n", destination);

    return 0;
}