#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t buffer_size = 1024; // Define the desired buffer size

    void *buffer = malloc(buffer_size);
    
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < 5; ++i) { // Loop to free the buffer multiple times
        free(buffer);                 // Free the memory allocated

        // Optionally re-allocate or handle it differently here, e.g., set NULL after freeing
        buffer = malloc(buffer_size);

        if (buffer == NULL && i < 4) {
            fprintf(stderr, "Memory reallocation failed\n");
            return EXIT_FAILURE;
        }
    }

    free(buffer); // Final free to ensure no memory leak

    return EXIT_SUCCESS;
}