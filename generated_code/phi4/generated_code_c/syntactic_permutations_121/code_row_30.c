#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 10;
    char *first_chunk = malloc(size);
    if (first_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Initialize the first chunk with some data
    for (size_t i = 0; i < size - 1; ++i) {
        first_chunk[i] = 'A' + i;
    }
    first_chunk[size - 1] = '\0';

    // Print contents of the first chunk
    printf("First Chunk: %s\n", first_chunk);

    // Allocate second chunk and copy data from the first chunk
    char *second_chunk = malloc(size);
    if (second_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        return EXIT_FAILURE;
    }

    strcpy(second_chunk, first_chunk);

    // Free memory of the first chunk
    free(first_chunk);

    // Print contents of the second chunk
    printf("Second Chunk: %s\n", second_chunk);

    // Free memory of the second chunk
    free(second_chunk);

    return EXIT_SUCCESS;
}