#include <stdio.h>
#include <string.h>

void memcpy_custom(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *) dest;
    const unsigned char *s = (const unsigned char *) src;

    while (n--) {
        *d++ = *s++;
    }
}

int main() {
    char source[] = "Hello, World!";
    char buffer[20];

    memcpy_custom(buffer, source, sizeof(source) - 1);
    
    printf("Copied message: %s\n", buffer);

    return 0;
}