#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t length = 10;
    
    // Allocate two chunks of memory
    char *firstChunk = (char *)malloc(length);
    if (firstChunk == NULL) {
        fprintf(stderr, "Memory allocation failed for first chunk\n");
        return EXIT_FAILURE;
    }
    
    char *secondChunk = (char *)malloc(length);
    if (secondChunk == NULL) {
        free(firstChunk);
        fprintf(stderr, "Memory allocation failed for second chunk\n");
        return EXIT_FAILURE;
    }

    // Initialize the first chunk with some data
    snprintf(firstChunk, length, "Hello");

    // Copy contents of the first chunk into the second chunk
    strcpy(secondChunk, firstChunk);

    // Output to verify the copy operation
    printf("First Chunk: %s\n", firstChunk);
    printf("Second Chunk: %s\n", secondChunk);

    // Free allocated memory
    free(firstChunk);
    free(secondChunk);

    return EXIT_SUCCESS;
}