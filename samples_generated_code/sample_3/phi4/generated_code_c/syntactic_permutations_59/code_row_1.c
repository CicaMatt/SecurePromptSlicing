#include <stdio.h>
#include <stdlib.h>

int main() {
    int buffer_size = 100; // Example buffer size, adjust as needed

    if (buffer_size <= 0) {
        fprintf(stderr, "Buffer size must be positive\n");
        return 1;
    }

    unsigned char *buffer = malloc(buffer_size);
    if (!buffer) {
        perror("Failed to allocate memory");
        return 1;
    }

    for (int i = 0; i < buffer_size; ++i) {
        buffer[i] = 'A';
    }

    // Buffer is now filled with 'A' characters
    // Example: print the first few elements of the buffer
    printf("Buffer content:\n");
    for (int i = 0; i < buffer_size && i < 10; ++i) {
        printf("%c ", buffer[i]);
    }
    printf("\n");

    free(buffer);
    return 0;
}