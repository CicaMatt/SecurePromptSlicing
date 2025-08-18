#include <stdio.h>
#include <string.h>

void memcpy_custom(void *dest, const void *src, size_t n) {
    char *d = (char *)dest;
    const char *s = (const char *)src;
    for (size_t i = 0; i < n; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char dest[6]; // Allocate space for "Hello" + null terminator
    const char src[] = "Hello";

    memcpy_custom(dest, src, strlen(src) + 1);

    printf("%s\n", dest);
    
    return 0;
}