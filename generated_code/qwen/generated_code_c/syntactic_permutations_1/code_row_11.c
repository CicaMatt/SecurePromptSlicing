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
    char source[] = "Hello, World!";
    char destination[20];

    custom_memcpy(destination, source, strlen(source) + 1);

    printf("Copied string: %s\n", destination);
    return 0;
}