#include <stdio.h>

void copy_bytes(void *dest, const void *src, size_t num) {
    unsigned char *d = dest;
    const unsigned char *s = src;
    for (size_t i = 0; i < num; ++i) {
        d[i] = s[i];
    }
}

int main() {
    unsigned char buffer[10];
    const char *source = "Hello";
    size_t length = sizeof("Hello") - 1;

    copy_bytes(buffer, source, length);

    printf("%s\n", buffer);
    
    return 0;
}