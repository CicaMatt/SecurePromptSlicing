#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Size for both memory allocations
    size_t size = 10;

    // Allocate first chunk of memory and initialize it with some values
    char *firstChunk = (char *)malloc(size);
    if (!firstChunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    for (size_t i = 0; i < size - 1; ++i) {
        firstChunk[i] = 'A' + i;
    }
    firstChunk[size - 1] = '\0'; // Null-terminate the string

    // Allocate second chunk of memory
    char *secondChunk = (char *)malloc(size);
    if (!secondChunk) {
        fprintf(stderr, "Memory allocation failed\n");
        free(firstChunk);
        return 1;
    }

    // Copy contents from firstChunk to secondChunk
    memcpy(secondChunk, firstChunk, size);

    // Print the contents of the second chunk
    printf("Contents of second chunk: %s\n", secondChunk);

    // Free allocated memory
    free(firstChunk);
    free(secondChunk);

    return 0;
}