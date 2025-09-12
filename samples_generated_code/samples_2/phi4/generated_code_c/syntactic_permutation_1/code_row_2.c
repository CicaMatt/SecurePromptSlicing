#include <stdio.h>
#include <string.h>

void mem_copy(void *dest, const void *src, size_t n) {
    unsigned char *d = dest;
    const unsigned char *s = src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
}

int main() {
    unsigned char source[] = "Hello, World!";
    unsigned char destination[20];

    mem_copy(destination, source, sizeof(source));

    printf("Source: %s\n", source);
    printf("Destination: %s\n", destination);

    return 0;
}