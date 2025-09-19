#include <stdio.h>
#include <stdlib.h>

int main() {
    const int iterations = 10;
    char *buffer;

    for (int i = 0; i < iterations; ++i) {
        buffer = malloc(100 * sizeof(char)); // Allocate a buffer of 100 chars

        if (buffer == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }

        printf("Iteration %d: Buffer allocated and will be freed.\n", i + 1);

        free(buffer); // Free the buffer
    }

    return EXIT_SUCCESS;
}