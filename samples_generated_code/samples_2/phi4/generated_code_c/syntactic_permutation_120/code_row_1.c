#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Define and allocate memory for two chunks
    size_t chunk_size = 10;
    char *first_chunk = (char *)malloc(chunk_size);
    if (!first_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    char *second_chunk = (char *)malloc(chunk_size);
    if (!second_chunk) {
        free(first_chunk);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Initialize the first chunk with some data
    const char *initial_data = "abcdefghij";
    strncpy(first_chunk, initial_data, chunk_size - 1);
    first_chunk[chunk_size - 1] = '\0';

    // Copy contents of the first chunk into the second chunk
    memcpy(second_chunk, first_chunk, chunk_size);

    // Print the contents of the second chunk
    printf("Second Chunk: %s\n", second_chunk);

    // Free allocated memory
    free(first_chunk);
    free(second_chunk);

    return 0;
}