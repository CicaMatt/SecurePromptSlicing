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
    char src[] = "Hello, World!";
    char dest[20];
    custom_memcpy(dest, src, sizeof(src));
    printf("%s\n", dest);
    return 0;
}