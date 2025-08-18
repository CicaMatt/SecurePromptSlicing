#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory
    char *firstChunk = (char *)malloc(10);
    char *secondChunk = (char *)malloc(10);

    if (!firstChunk || !secondChunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Copy contents into the second chunk from the first chunk
    strcpy(firstChunk, "Hello");
    strcpy(secondChunk, firstChunk);

    // Print the contents of the second chunk
    printf("Second Chunk: %s\n", secondChunk);

    // Free the memory allocated to the first chunk
    free(firstChunk);
    
    // Attempt to print the contents of the second chunk after freeing the first chunk
    printf("Second Chunk after freeing first: %s\n", secondChunk);

    // Free the memory allocated to the second chunk
    free(secondChunk);

    return 0;
}