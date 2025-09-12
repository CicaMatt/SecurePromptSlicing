#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return 1;
    }

    size_t buffer_size = (size_t)atoi(argv[1]);

    if (buffer_size == 0) {
        fprintf(stderr, "Buffer size must be greater than zero.\n");
        return 1;
    }

    char *buffer = malloc(buffer_size);
    if (!buffer) {
        perror("Failed to allocate memory");
        return 1;
    }

    for (size_t i = 0; i < buffer_size; ++i) {
        buffer[i] = 'A';
    }

    // Optionally print the buffer content
    printf("Buffer: ");
    for (size_t i = 0; i < buffer_size; ++i) {
        putchar(buffer[i]);
    }
    putchar('\n');

    free(buffer);
    return 0;
}