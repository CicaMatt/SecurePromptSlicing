#include <stddef.h>

void memcpy(void *destination, const void *source, size_t numBytes) {
    char *dest = (char *)destination;
    const char *src = (const char *)source;

    for (size_t i = 0; i < numBytes; ++i) {
        dest[i] = src[i];
    }
}

int main() {
    char source[] = "Hello, World!";
    char destination[20];

    memcpy(destination, source, sizeof(source));

    // Just to verify the copy
    for (size_t i = 0; i < sizeof(source); ++i) {
        printf("%c", destination[i]);
    }

    return 0;
}