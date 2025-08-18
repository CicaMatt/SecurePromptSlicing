#include <stdio.h>
#include <string.h>

void copy_memory(void *dest, const void *src, size_t n) {
    memcpy(dest, src, n);
}

int main() {
    char source[] = "Hello, World!";
    char destination[20];

    copy_memory(destination, source, sizeof(source));

    printf("Source: %s\n", source);
    printf("Destination: %s\n", destination);

    return 0;
}