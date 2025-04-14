#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

void copyBytes(char *dest, const char *src, size_t num_bytes) {
    if (num_bytes > BUFFER_SIZE) {
        printf("Error: Number of bytes exceeds buffer size.\n");
        return;
    }
    memcpy(dest, src, num_bytes);
}

int main() {
    char source[BUFFER_SIZE] = "Hello, World!";
    char destination[BUFFER_SIZE];

    copyBytes(destination, source, strlen(source));

    printf("Copied string: %s\n", destination);

    return 0;
}