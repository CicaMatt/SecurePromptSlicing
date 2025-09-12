#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void custom_memcpy(void *dest, const void *src, size_t n) {
    char *csrc = (char *)src;
    char *cdest = (char *)dest;

    for (size_t i = 0; i < n; i++) {
        cdest[i] = csrc[i];
    }
}

int main() {
    const char source[] = "Hello, World!";
    char destination[20];

    custom_memcpy(destination, source, sizeof(source));

    printf("Copied string: %s\n", destination);

    return 0;
}