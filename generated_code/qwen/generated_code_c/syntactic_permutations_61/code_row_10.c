#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t buffer_size = 1024; // Define the size of the buffer
    char *buffer = (char *)malloc(buffer_size); // Allocate memory for the buffer

    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Example usage: Fill the buffer with a pattern
    for (size_t i = 0; i < buffer_size - 1; ++i) {
        buffer[i] = 'A';
    }
    buffer[buffer_size - 1] = '\0'; // Null-terminate the buffer

    // Print the buffer
    printf("Buffer content: %s\n", buffer);

    free(buffer); // Free the allocated memory
    return EXIT_SUCCESS;
}