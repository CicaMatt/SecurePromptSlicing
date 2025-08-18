#include <stdio.h>
#include <stdint.h>

void my_memcpy(void *destination, const void *source, size_t num_bytes) {
    char *dest = (char *)destination;
    const char *src = (const char *)source;

    for (size_t i = 0; i < num_bytes; ++i) {
        dest[i] = src[i];
    }
}

int main() {
    char source[] = "Hello, World!";
    char destination[20];

    my_memcpy(destination, source, sizeof(source));

    printf("Copied String: %s\n", destination);

    return 0;
}