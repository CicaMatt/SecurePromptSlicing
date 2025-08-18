#include <stdio.h>

void *memcpy(void *dest, const void *src, size_t n) {
    char *d = (char *)dest;
    const char *s = (const char *)src;
    while (n--) {
        *d++ = *s++;
    }
    return dest;
}

int main() {
    char src[] = "Hello, World!";
    char dest[20];
    memcpy(dest, src, sizeof(src));
    printf("%s\n", dest);
    return 0;
}