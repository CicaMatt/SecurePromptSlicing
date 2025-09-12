#include <stdio.h>
#include <string.h>

void copy_bytes(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    for (size_t i = 0; i < n; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char buffer[20];

    copy_bytes(buffer, "Hello", 6); // Including null terminator

    printf("%s\n", buffer);

    return 0;
}