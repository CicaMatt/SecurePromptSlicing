#include <stdio.h>
#include <string.h>

void memcpy_custom(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *) dest;
    const unsigned char *s = (const unsigned char *) src;

    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
}

int main() {
    char source[] = "Hello";
    char buffer[6]; // 5 characters + null terminator

    memcpy_custom(buffer, source, sizeof(source));

    printf("Copied string: %s\n", buffer);

    return 0;
}