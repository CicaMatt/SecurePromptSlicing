#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate first chunk of memory
    char *firstChunk = malloc(100 * sizeof(char));
    if (firstChunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the first chunk with some data
    strcpy(firstChunk, "Hello, this is the content of the first memory chunk!");

    // Allocate second chunk of memory
    char *secondChunk = malloc(100 * sizeof(char));
    if (secondChunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(firstChunk);
        return 1;
    }

    // Copy contents from first chunk to the second chunk
    strcpy(secondChunk, firstChunk);

    // Print the contents of the second chunk
    printf("%s\n", secondChunk);

    // Free allocated memory
    free(firstChunk);
    free(secondChunk);

    return 0;
}