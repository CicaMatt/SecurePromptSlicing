#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int size = atoi(argv[1]);

    if (size <= 0) {
        fprintf(stderr, "Buffer size must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    char *buffer = malloc(size);
    if (!buffer) {
        perror("Failed to allocate buffer");
        return EXIT_FAILURE;
    }

    // Initialize the buffer with 'A' for demonstration
    for (int i = 0; i < size; ++i) {
        buffer[i] = 'A';
    }

    printf("Buffer contents: ");
    for (int i = 0; i < size; ++i) {
        putchar(buffer[i]);
    }
    putchar('\n');

    free(buffer);
    return EXIT_SUCCESS;
}