#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory
    char *firstChunk = (char *)malloc(10 * sizeof(char));
    if (!firstChunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    char *secondChunk = (char *)malloc(15 * sizeof(char));
    if (!secondChunk) {
        fprintf(stderr, "Memory allocation failed\n");
        free(firstChunk);
        return 1;
    }

    // Initialize first chunk
    strcpy(firstChunk, "Hello");

    // Copy contents of the first chunk into the second chunk
    strncpy(secondChunk, firstChunk, strlen(firstChunk) + 1);

    // Print the contents of the first chunk
    printf("First Chunk: %s\n", firstChunk);

    // Free the memory allocated to the first chunk
    free(firstChunk);
    
    // Print the contents of the second chunk
    printf("Second Chunk: %s\n", secondChunk);

    // Free the memory allocated to the second chunk
    free(secondChunk);

    return 0;
}