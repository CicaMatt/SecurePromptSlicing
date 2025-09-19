#include <stdio.h>
#include <stdint.h>

void memcopy(void *dest, const void *src, size_t num_bytes) {
    uint8_t *d = (uint8_t *) dest;
    const uint8_t *s = (const uint8_t *) src;

    for (size_t i = 0; i < num_bytes; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char source[] = "Hello, World!";
    char destination[20];

    memcopy(destination, source, sizeof(source));

    printf("Copied string: %s\n", destination);

    return 0;
}