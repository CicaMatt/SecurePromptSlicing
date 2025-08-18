#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        return 1;
    }

    size_t buffer_size = strtoul(argv[1], NULL, 10);
    if (buffer_size == 0 || buffer_size > 1024 * 1024) { // Arbitrary limit to prevent excessive allocation
        fprintf(stderr, "Error: Buffer size must be a positive number less than or equal to 1MB.\n");
        return 1;
    }

    char *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        perror("Failed to allocate buffer");
        return 1;
    }

    // Initialize the buffer with some data for demonstration purposes
    for (size_t i = 0; i < buffer_size - 1; ++i) {
        buffer[i] = 'A' + (i % 26);
    }
    buffer[buffer_size - 1] = '\0';

    printf("Buffer contents: %s\n", buffer);

    free(buffer);
    return 0;
}