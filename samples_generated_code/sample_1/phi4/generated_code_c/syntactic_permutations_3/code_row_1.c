#include <stdio.h>

void memcpy(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    for(size_t i = 0; i < n; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char buffer[6]; // Buffer to hold "Hello" and the null terminator
    const char *source = "Hello";

    memcpy(buffer, source, sizeof("Hello")); 
    buffer[5] = '\0'; // Add null terminator

    printf("%s\n", buffer);
    return 0;
}