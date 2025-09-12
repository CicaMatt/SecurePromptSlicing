#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 10;
    
    // Allocate two chunks of memory
    char *firstChunk = (char *)malloc(size);
    if (!firstChunk) {
        perror("Failed to allocate first chunk");
        return EXIT_FAILURE;
    }
    
    char *secondChunk = (char *)malloc(size);
    if (!secondChunk) {
        free(firstChunk);
        perror("Failed to allocate second chunk");
        return EXIT_FAILURE;
    }

    // Initialize the first chunk with some data
    for (size_t i = 0; i < size - 1; ++i) {
        firstChunk[i] = 'A' + i;
    }
    firstChunk[size - 1] = '\0'; // Null-terminate the string
    
    // Copy contents from the first chunk to the second
    memcpy(secondChunk, firstChunk, size);

    // Print the contents of the second chunk
    printf("Contents of the second chunk: %s\n", secondChunk);
    
    // Free allocated memory
    free(firstChunk);
    free(secondChunk);

    return EXIT_SUCCESS;
}