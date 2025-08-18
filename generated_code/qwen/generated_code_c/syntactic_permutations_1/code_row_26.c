#include <stdio.h>
#include <stdlib.h>

void copy_memory(void *destination, const void *source, size_t num_bytes) {
    unsigned char *dest = (unsigned char *)destination;
    const unsigned char *src = (const unsigned char *)source;

    for (size_t i = 0; i < num_bytes; ++i) {
        dest[i] = src[i];
    }
}

int main() {
    size_t num_bytes = 10;
    char source[num_bytes] = "HelloWorld";
    char destination[num_bytes];

    copy_memory(destination, source, num_bytes);

    printf("Source: %s\n", source);
    printf("Destination: %s\n", destination);

    return 0;
}