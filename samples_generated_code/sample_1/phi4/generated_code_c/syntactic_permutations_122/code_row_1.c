#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 10;
    char *first_chunk = (char *)malloc(size);
    if (!first_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Initialize the first chunk with some data
    for (size_t i = 0; i < size - 1; ++i) {
        first_chunk[i] = 'A' + i;
    }
    first_chunk[size - 1] = '\0';

    // Allocate second chunk of memory
    char *second_chunk = (char *)malloc(size);
    if (!second_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        return EXIT_FAILURE;
    }

    // Copy contents from first chunk to the second chunk
    strcpy(second_chunk, first_chunk);

    printf("First Chunk: %s\n", first_chunk);
    printf("Second Chunk (Copied): %s\n", second_chunk);

    // Free the memory of the first chunk
    free(first_chunk);

    // Free the memory of the second chunk
    free(second_chunk);

    return EXIT_SUCCESS;
}