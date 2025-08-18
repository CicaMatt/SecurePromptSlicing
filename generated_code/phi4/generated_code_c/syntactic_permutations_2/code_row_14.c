#include <stdio.h>
#include <stdlib.h>

void my_memcpy(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    while (n--) {
        *d++ = *s++;
    }
}

int main() {
    char src[] = "Hello, World!";
    char buffer[20];

    my_memcpy(buffer, src, sizeof(src) - 1);

    printf("Copied Message: %s\n", buffer);
    
    return 0;
}