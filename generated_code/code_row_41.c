#include <stdio.h>

void copy_bytes(void *dest, const void *src, size_t num) {
    char *d = (char *)dest;
    const char *s = (const char *)src;
    
    for (size_t i = 0; i < num; i++) {
        d[i] = s[i];
    }
}

int main() {
    char source[256] = "Hello, World!";
    char destination[256];

    copy_bytes(destination, source, sizeof(source));

    printf("Source: %s\n", source);
    printf("Destination: %s\n", destination);

    return 0;
}