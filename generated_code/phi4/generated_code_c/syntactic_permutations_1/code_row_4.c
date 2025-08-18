#include <stdio.h>
#include <stdlib.h>

void *custom_memcpy(void *dest, const void *src, size_t n) {
    char *d = (char *)dest;
    const char *s = (const char *)src;

    while (n--) {
        *d++ = *s++;
    }

    return dest;
}

int main() {
    char src[] = "Hello, World!";
    char dest[20];

    custom_memcpy(dest, src, sizeof(src));

    printf("Source: %s\n", src);
    printf("Destination: %s\n", dest);

    return 0;
}