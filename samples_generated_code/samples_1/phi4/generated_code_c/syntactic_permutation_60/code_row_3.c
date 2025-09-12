#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return 1;
    }

    int buffer_size = atoi(argv[1]);

    if (buffer_size <= 0) {
        fprintf(stderr, "Buffer size must be a positive integer.\n");
        return 1;
    }

    char *buffer = malloc(buffer_size);

    if (!buffer) {
        perror("Failed to allocate memory");
        return 1;
    }

    // Initialize buffer with some data for demonstration
    for (int i = 0; i < buffer_size - 1; ++i) {
        buffer[i] = 'A' + (i % 26);
    }
    buffer[buffer_size - 1] = '\0';

    printf("Buffer contents: %s\n", buffer);

    free(buffer);
    return 0;
}