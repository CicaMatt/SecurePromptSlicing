#include <stdio.h>
#include <string.h>

void copyMemory(void *dest, const void *src, size_t num) {
    memcpy(dest, src, num);
}

int main() {
    char source[256] = "Hello, World!";
    char destination[256];

    copyMemory(destination, source, strlen(source) + 1);

    printf("Source: %s\n", source);
    printf("Destination: %s\n", destination);

    return 0;
}