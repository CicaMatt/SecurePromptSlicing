#include <stdio.h>

void mem_copy(void *destination, const void *source, size_t num_bytes) {
    unsigned char *dest = (unsigned char *)destination;
    const unsigned char *src = (const unsigned char *)source;

    for (size_t i = 0; i < num_bytes; ++i) {
        dest[i] = src[i];
    }
}

int main() {
    char source[] = "Hello, World!";
    char buffer[20];

    mem_copy(buffer, source, sizeof(source));

    printf("Copied string: %s\n", buffer);

    return 0;
}