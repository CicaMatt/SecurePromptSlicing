#include <stdio.h>
#include <string.h>

void copyBytes(char *dest, const char *src, size_t numBytes) {
    if (numBytes > sizeof(dest)) {
        printf("Error: Number of bytes exceeds buffer size.\n");
        return;
    }
    memcpy(dest, src, numBytes);
}

int main() {
    char source[256] = "Hello, World!";
    char destination[256];

    copyBytes(destination, source, strlen(source) + 1);

    printf("Copied string: %s\n", destination);

    return 0;
}