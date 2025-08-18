#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t buffer_size = 1024; // Example buffer size

    void *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < 10; ++i) { // Free the buffer in a loop
        free(buffer);

        // Allocate again to avoid using freed memory
        buffer = malloc(buffer_size);
        if (buffer == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
    }

    free(buffer); // Final free after the loop

    printf("Buffer allocated and freed successfully.\n");

    return 0;
}