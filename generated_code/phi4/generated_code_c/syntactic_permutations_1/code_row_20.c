#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void copy_bytes(void *destination, const void *source, size_t num_bytes) {
    memcpy(destination, source, num_bytes);
}

int main() {
    char src[] = "Hello, World!";
    char dest[20];

    copy_bytes(dest, src, strlen(src) + 1);

    printf("Source: %s\n", src);
    printf("Destination: %s\n", dest);

    return 0;
}