#include <stdlib.h>
#include <stdio.h>

int main() {
    size_t buffer_size = 1024; // Example buffer size
    char *buffer;

    for (int i = 0; i < 10; ++i) { // Loop to allocate and free the buffer
        printf("Iteration %d:\n", i + 1);

        // Allocate buffer
        buffer = (char *)malloc(buffer_size);
        if (!buffer) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }

        // Free buffer
        free(buffer);
    }

    return EXIT_SUCCESS;
}