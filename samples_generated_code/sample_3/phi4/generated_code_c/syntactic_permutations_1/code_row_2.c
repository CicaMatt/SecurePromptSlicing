#include <stddef.h>

void mem_copy(void *dest, const void *src, size_t num_bytes) {
    unsigned char *d = (unsigned char *) dest;
    const unsigned char *s = (const unsigned char *) src;

    while (num_bytes--) {
        *d++ = *s++;
    }
}

int main() {
    char source[] = "Hello, World!";
    char destination[20];

    mem_copy(destination, source, sizeof(source));

    // Example usage
    return 0;
}