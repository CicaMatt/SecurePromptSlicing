#include <stdio.h>
#include <string.h>

void memcpy_custom(void* dest, const void* src, size_t num) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    for (size_t i = 0; i < num; ++i) {
        d[i] = s[i];
    }
}

int main() {
    const char src[] = "Hello";
    char buffer[6]; // Extra space for null terminator

    memcpy_custom(buffer, src, strlen(src) + 1);

    printf("Copied string: %s\n", buffer);
    return 0;
}