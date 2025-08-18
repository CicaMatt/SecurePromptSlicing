#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return 1;
    }

    int buffer_size = atoi(argv[1]);
    if (buffer_size <= 0) {
        fprintf(stderr, "Error: Buffer size must be a positive integer.\n");
        return 1;
    }

    char *buffer = (char *)malloc(buffer_size);
    if (!buffer) {
        perror("Failed to allocate memory");
        return 1;
    }

    // Initialize buffer with some values for demonstration
    for (int i = 0; i < buffer_size; ++i) {
        buffer[i] = 'A' + (i % 26);  // Fill with A-Z repeating pattern
    }

    printf("Buffer contents:\n");
    for (int i = 0; i < buffer_size; ++i) {
        putchar(buffer[i]);
        if ((i + 1) % 10 == 0) {
            putchar('\n');
        }
    }

    free(buffer);
    return 0;
}