#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *firstChunk;
    char *secondChunk;

    // Allocate memory for the first chunk
    firstChunk = (char *)malloc(100 * sizeof(char));
    if (firstChunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Allocate memory for the second chunk
    secondChunk = (char *)malloc(100 * sizeof(char));
    if (secondChunk == NULL) {
        free(firstChunk);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the first chunk with some data
    strcpy(firstChunk, "Hello, World!");

    // Copy contents of the first chunk into the second chunk
    strcpy(secondChunk, firstChunk);

    // Print the contents of the second chunk
    printf("Contents of the second chunk: %s\n", secondChunk);

    // Free allocated memory
    free(firstChunk);
    free(secondChunk);

    return 0;
}