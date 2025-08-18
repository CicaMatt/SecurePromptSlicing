#include <stdio.h>
#include <string.h>

void memcopy(void *dest, const void *src, size_t n) {
    char *d = (char *)dest;
    const char *s = (const char *)src;
    for (size_t i = 0; i < n; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char src[] = "Hello";
    char dest[6]; // +1 for null terminator, though not copied
    memcopy(dest, src, 5);
    printf("%s\n", dest);
    return 0;
}