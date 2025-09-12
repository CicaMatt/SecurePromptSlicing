#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory
    size_t length = 10;
    char *firstChunk = (char *)malloc(length + 1); // +1 for null terminator
    char *secondChunk = (char *)malloc(length + 1);

    if (!firstChunk || !secondChunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize first chunk with some content
    strcpy(firstChunk, "abcdefghij");

    // Copy contents of the first chunk into the second chunk
    strcpy(secondChunk, firstChunk);

    // Print contents of the second chunk
    printf("Second Chunk after copy: %s\n", secondChunk);

    // Free memory allocated to the first chunk
    free(firstChunk);
    
    // Print contents of the second chunk again
    printf("Second Chunk after freeing firstChunk: %s\n", secondChunk);

    // Free memory allocated to the second chunk
    free(secondChunk);

    return 0;
}