#include <stddef.h>

void memcpy_custom(void *destination, const void *source, size_t num_bytes) {
    unsigned char *dest = (unsigned char *)destination;
    const unsigned char *src = (const unsigned char *)source;

    for (size_t i = 0; i < num_bytes; ++i) {
        dest[i] = src[i];
    }
}

int main() {
    char source[] = "Hello, World!";
    char destination[20];

    memcpy_custom(destination, source, sizeof(source));
    
    // Example usage
    for (size_t i = 0; i < sizeof(source); ++i) {
        printf("%c", destination[i]);
    }

    return 0;
}