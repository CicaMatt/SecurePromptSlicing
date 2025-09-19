#include <stdio.h>
#include <stdlib.h>

int main() {
    int iterations = 10;
    size_t bufferSize = 256;

    for (int i = 0; i < iterations; ++i) {
        char *buffer = malloc(bufferSize);
        
        if (buffer == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
        
        // Simulate some operations with the buffer
        snprintf(buffer, bufferSize, "Buffer iteration %d", i);

        free(buffer);
    }

    printf("All buffers freed successfully.\n");

    return EXIT_SUCCESS;
}