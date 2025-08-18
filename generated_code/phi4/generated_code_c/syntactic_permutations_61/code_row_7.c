#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t buffer_size = 1024; // Example buffer size

    // Allocate memory
    char *buffer = (char *)malloc(buffer_size);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Free the buffer in a loop
    for (int i = 0; i < 10; ++i) { // Example loop count of 10 iterations
        free(buffer);

        // Reallocate to demonstrate repeated freeing and reusing logic
        buffer = (char *)malloc(buffer_size);
        if (!buffer) {
            fprintf(stderr, "Memory reallocation failed\n");
            return EXIT_FAILURE;
        }
    }

    // Final free after loop completion
    free(buffer);

    return 0;
}