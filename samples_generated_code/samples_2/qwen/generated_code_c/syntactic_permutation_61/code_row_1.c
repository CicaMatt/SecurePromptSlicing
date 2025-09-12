#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t buffer_size = 1024;
    char *buffer = (char *)malloc(buffer_size);

    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Example usage: Initialize the buffer with zeros
    for (size_t i = 0; i < buffer_size; ++i) {
        buffer[i] = 0;
    }

    // Free the allocated memory
    free(buffer);

    return EXIT_SUCCESS;
}