#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void custom_memcpy(void *dest, const void *src, size_t n) {
    char *cdest = (char *)dest;
    const char *csrc = (const char *)src;

    for (size_t i = 0; i < n; i++) {
        cdest[i] = csrc[i];
    }
}

int main() {
    char src[] = "Hello, World!";
    char dest[20];

    custom_memcpy(dest, src, sizeof(src));

    printf("Copied string: %s\n", dest);

    return 0;
}