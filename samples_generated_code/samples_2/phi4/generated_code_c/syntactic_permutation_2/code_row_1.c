#include <stdio.h>

void memcpy_custom(void *dest, const void *src, size_t n) {
    char *d = (char *)dest;
    const char *s = (const char *)src;
    
    for(size_t i = 0; i < n; ++i) {
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