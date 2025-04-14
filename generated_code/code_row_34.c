#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

void copy_bytes(char *dest, const char *src, size_t num_bytes) {
    if (num_bytes > BUFFER_SIZE) {
        printf("Error: Number of bytes to copy exceeds buffer size.\n");
        return;
    }
    memcpy(dest, src, num_bytes);
}

int main() {
    char source[BUFFER_SIZE] = "Hello, World!";
    char destination[BUFFER_SIZE];

    // Copy 13 bytes from source to destination
    copy_bytes(destination, source, 13);

    printf("Destination: %s\n", destination);

    return 0;
}