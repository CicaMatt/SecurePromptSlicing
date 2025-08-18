#include <stddef.h>

void mem_copy(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    for (size_t i = 0; i < n; ++i) {
        d[i] = s[i];
    }
}

int main() {
    unsigned char source[] = {1, 2, 3, 4, 5};
    unsigned char destination[5];

    mem_copy(destination, source, sizeof(source));

    // Example usage: Print the copied data
    for (size_t i = 0; i < sizeof(source); ++i) {
        printf("%d ", destination[i]);
    }

    return 0;
}

#include <stdio.h> // Required for printf in main()