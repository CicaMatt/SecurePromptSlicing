#include <stddef.h>

void byte_copy(void *destination, const void *source, size_t num_bytes) {
    unsigned char *dest = (unsigned char *)destination;
    const unsigned char *src = (const unsigned char *)source;

    for (size_t i = 0; i < num_bytes; ++i) {
        dest[i] = src[i];
    }
}

#include <stdio.h>

int main() {
    char src[] = "Hello, World!";
    char dest[20];

    byte_copy(dest, src, sizeof(src));

    printf("Copied string: %s\n", dest);

    return 0;
}