#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t buffer_size = 1024;
    void *buffer = malloc(buffer_size);

    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < 5; i++) {
        free(buffer);
        buffer = NULL;
        // Reallocate memory to simulate multiple allocations and frees
        buffer = malloc(buffer_size);
        if (buffer == NULL) {
            fprintf(stderr, "Memory allocation failed on iteration %zu\n", i + 1);
            return EXIT_FAILURE;
        }
    }

    free(buffer); // Final free after loop

    return EXIT_SUCCESS;
}