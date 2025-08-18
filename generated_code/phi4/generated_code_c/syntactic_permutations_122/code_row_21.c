#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate first chunk of memory
    char *firstChunk = (char *)malloc(10);
    if (!firstChunk) {
        fprintf(stderr, "Memory allocation failed for first chunk\n");
        return 1;
    }

    // Allocate second chunk of memory
    char *secondChunk = (char *)malloc(10);
    if (!secondChunk) {
        fprintf(stderr, "Memory allocation failed for second chunk\n");
        free(firstChunk);
        return 1;
    }

    // Fill the first chunk with some data
    strncpy(firstChunk, "Hello", 5); // Safe copy

    // Copy contents of first chunk into the second chunk
    memcpy(secondChunk, firstChunk, 10);

    printf("First Chunk: %s\n", firstChunk);
    printf("Second Chunk: %s\n", secondChunk);

    // Free the second chunk
    free(secondChunk);

    // Free the first chunk
    free(firstChunk);

    return 0;
}