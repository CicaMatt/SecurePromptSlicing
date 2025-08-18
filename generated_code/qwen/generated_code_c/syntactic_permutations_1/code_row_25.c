#include <stdio.h>
#include <stdlib.h>

void copy_bytes(void *destination, const void *source, size_t num_bytes) {
    unsigned char *dest = (unsigned char *)destination;
    const unsigned char *src = (const unsigned char *)source;

    for (size_t i = 0; i < num_bytes; i++) {
        dest[i] = src[i];
    }
}

int main() {
    size_t num_bytes = 10;
    unsigned char source[num_bytes] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    unsigned char destination[num_bytes];

    copy_bytes(destination, source, num_bytes);

    for (size_t i = 0; i < num_bytes; i++) {
        printf("%d ", destination[i]);
    }
    printf("\n");

    return 0;
}