#include <stdio.h>

void memcpy_custom(void *dest, const void *src, size_t num) {
    unsigned char *d = (unsigned char *) dest;
    const unsigned char *s = (const unsigned char *) src;

    for (size_t i = 0; i < num; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char source[] = "Hello, World!";
    char buffer[20];

    memcpy_custom(buffer, source, sizeof(source));

    printf("Copied message: %s\n", buffer);

    return 0;
}