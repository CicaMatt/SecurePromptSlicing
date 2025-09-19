#include <stdio.h>
#include <string.h>

void custom_memcpy(void *dest, const void *src, size_t n) {
    char *d = (char *)dest;
    const char *s = (const char *)src;
    for (size_t i = 0; i < n; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char src[50] = "Hello, World!";
    char dest[50];
    custom_memcpy(dest, src, strlen(src) + 1);
    printf("%s\n", dest);
    return 0;
}