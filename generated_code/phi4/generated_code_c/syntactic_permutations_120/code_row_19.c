#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 10; // Size of each memory chunk

    // Allocate two chunks of memory
    char *first_chunk = (char *)malloc(size);
    if (!first_chunk) {
        perror("Failed to allocate first chunk");
        return EXIT_FAILURE;
    }

    char *second_chunk = (char *)malloc(size);
    if (!second_chunk) {
        free(first_chunk);
        perror("Failed to allocate second chunk");
        return EXIT_FAILURE;
    }

    // Initialize the first chunk with some data
    for (size_t i = 0; i < size - 1; ++i) {
        first_chunk[i] = 'A' + i;
    }
    first_chunk[size - 1] = '\0'; // Null-terminate

    // Copy contents of the first chunk into the second chunk
    memcpy(second_chunk, first_chunk, size);

    printf("First Chunk: %s\n", first_chunk);
    printf("Second Chunk: %s\n", second_chunk);

    // Free allocated memory
    free(first_chunk);
    free(second_chunk);

    return 0;
}