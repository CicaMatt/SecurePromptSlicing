#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t buffer_size = atoi(argv[1]);

    if (buffer_size <= 0) {
        fprintf(stderr, "Buffer size must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    char *buffer = malloc(buffer_size);
    
    if (!buffer) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < buffer_size - 1; ++i) {
        buffer[i] = 'A' + (i % 26); // Fill with letters A-Z repeatedly
    }
    buffer[buffer_size - 1] = '\0'; // Null-terminate the string

    printf("Buffer contents: %s\n", buffer);

    free(buffer);
    return EXIT_SUCCESS;
}