#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate first chunk of memory
    char *first_chunk = (char *)malloc(10);
    if (first_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the first chunk with some data
    strcpy(first_chunk, "Hello");

    // Allocate second chunk of memory
    char *second_chunk = (char *)malloc(10);
    if (second_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);  // Free already allocated memory before exiting
        return 1;
    }

    // Copy contents from first to second chunk
    strcpy(second_chunk, first_chunk);

    // Free the first chunk of memory
    free(first_chunk);

    // Print second chunk to verify copy
    printf("Second Chunk: %s\n", second_chunk);

    // Free the second chunk of memory
    free(second_chunk);

    return 0;
}