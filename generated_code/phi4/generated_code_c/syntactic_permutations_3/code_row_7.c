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
    char buffer[20];
    const char *source = "Hello";

    memcpy_custom(buffer, source, strlen(source) + 1);

    printf("%s\n", buffer);
    
    return 0;
}