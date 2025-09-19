#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory, each of size 10 bytes
    char *firstChunk = (char *)malloc(10);
    if (!firstChunk) {
        perror("Failed to allocate first chunk");
        return EXIT_FAILURE;
    }
    
    char *secondChunk = (char *)malloc(10);
    if (!secondChunk) {
        free(firstChunk); // Free the previously allocated memory
        perror("Failed to allocate second chunk");
        return EXIT_FAILURE;
    }

    // Initialize first chunk with some data
    strcpy(firstChunk, "Hello");

    // Copy contents of the first chunk into the second chunk
    strncpy(secondChunk, firstChunk, 10);
    
    // Free the first chunk
    free(firstChunk);

    // Free the second chunk
    free(secondChunk);

    return 0;
}