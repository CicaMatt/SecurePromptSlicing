#include <stdint.h>
#include <stddef.h>

void memcpy_custom(void *dest, const void *src, size_t num) {
    uint8_t *d = (uint8_t *) dest;
    const uint8_t *s = (const uint8_t *) src;

    for (size_t i = 0; i < num; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char source[] = "Hello, World!";
    char destination[20];

    memcpy_custom(destination, source, sizeof(source));

    return 0;
}