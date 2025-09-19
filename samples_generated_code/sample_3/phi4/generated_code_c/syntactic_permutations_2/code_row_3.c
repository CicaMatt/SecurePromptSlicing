#include <stdio.h>
#include <string.h>

void my_memcpy(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *) dest;
    const unsigned char *s = (const unsigned char *) src;

    for(size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
}

int main() {
    char source[] = "Hello, World!";
    char buffer[20];

    my_memcpy(buffer, source, sizeof(source));

    printf("Buffer: %s\n", buffer);

    return 0;
}