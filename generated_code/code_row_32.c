#include <stdio.h>

void copyBytes(char *dest, const char *src, size_t num_bytes) {
    if (num_bytes > 256) {
        printf("Error: Number of bytes exceeds buffer size.\n");
        return;
    }
    
    for (size_t i = 0; i < num_bytes; i++) {
        dest[i] = src[i];
    }
}

int main() {
    char source[256] = "Hello, World!";
    char destination[256];

    copyBytes(destination, source, 13);

    printf("Copied string: %s\n", destination);

    return 0;
}