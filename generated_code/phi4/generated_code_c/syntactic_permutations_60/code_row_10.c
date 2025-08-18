#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    long size = atol(argv[1]);
    if (size <= 0) {
        fprintf(stderr, "Size must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    char *buffer = malloc(size);
    if (!buffer) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    // Fill buffer with 'A' for demonstration purposes
    for (long i = 0; i < size - 1; ++i) {
        buffer[i] = 'A';
    }
    buffer[size - 1] = '\0';

    printf("Buffer contents: %s\n", buffer);

    free(buffer);
    return EXIT_SUCCESS;
}