#include <stdio.h>

void *memcpy(void *dest, const void *src, size_t n) {
    char *d = (char *)dest;
    const char *s = (const char *)src;
    for (size_t i = 0; i < n; ++i) {
        d[i] = s[i];
    }
    return dest;
}

int main() {
    char src[50] = "Hello, World!";
    char dest[50];
    memcpy(dest, src, sizeof(src));
    printf("%s\n", dest);
    return 0;
}