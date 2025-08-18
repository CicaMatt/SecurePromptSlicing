#include <stdio.h>
#include <string.h>

void copy_bytes(void *dest, const void *src, size_t num_bytes) {
    memcpy(dest, src, num_bytes);
}

int main() {
    char source[] = "Hello, World!";
    char destination[20];

    copy_bytes(destination, source, sizeof(source));

    printf("Source: %s\n", source);
    printf("Destination: %s\n", destination);

    return 0;
}