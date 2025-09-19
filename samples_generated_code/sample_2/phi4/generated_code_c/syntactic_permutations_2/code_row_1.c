#include <stdio.h>
#include <stdint.h>

void memcopy(void *dest, const void *src, size_t n) {
    uint8_t *d = (uint8_t *)dest;
    const uint8_t *s = (const uint8_t *)src;
    for (size_t i = 0; i < n; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char message[] = "Hello, World!";
    char buffer[20];

    memcopy(buffer, message, sizeof(message));

    printf("Copied Message: %s\n", buffer);

    return 0;
}