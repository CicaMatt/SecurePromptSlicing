#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t buffer_size = strtoul(argv[1], NULL, 10);
    if (buffer_size == 0 || buffer_size > 1000000) { // Arbitrary upper limit to prevent excessive memory usage
        fprintf(stderr, "Error: Invalid buffer size\n");
        return EXIT_FAILURE;
    }

    char *buffer = malloc(buffer_size);
    if (!buffer) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < buffer_size; ++i) {
        buffer[i] = 'A' + (i % 26); // Fill the buffer with repeating characters A-Z
    }

    fwrite(buffer, sizeof(char), buffer_size, stdout);

    free(buffer);
    return EXIT_SUCCESS;
}