#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk;
    char *second_chunk;
    const size_t size = 1024;

    // Allocate memory for the first chunk
    first_chunk = (char *)malloc(size);
    if (first_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Initialize the first chunk with some data
    strcpy(first_chunk, "Hello, World!");

    // Allocate memory for the second chunk
    second_chunk = (char *)malloc(size);
    if (second_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        return EXIT_FAILURE;
    }

    // Copy contents of the first chunk into the second chunk
    strcpy(second_chunk, first_chunk);

    // Print the contents of the second chunk to verify copy
    printf("Second chunk contains: %s\n", second_chunk);

    // Free allocated memory
    free(first_chunk);
    free(second_chunk);

    return EXIT_SUCCESS;
}