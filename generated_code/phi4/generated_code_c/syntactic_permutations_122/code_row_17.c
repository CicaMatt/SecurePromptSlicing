#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate first chunk of memory
    char *firstChunk = (char *)malloc(10 * sizeof(char));
    if (!firstChunk) {
        perror("Failed to allocate memory for first chunk");
        return EXIT_FAILURE;
    }

    // Initialize the first chunk with some data
    strcpy(firstChunk, "Hello123");

    // Allocate second chunk of memory
    char *secondChunk = (char *)malloc(10 * sizeof(char));
    if (!secondChunk) {
        perror("Failed to allocate memory for second chunk");
        free(firstChunk);
        return EXIT_FAILURE;
    }

    // Copy contents from first chunk to the second chunk
    strcpy(secondChunk, firstChunk);

    // Free the first chunk
    free(firstChunk);

    // Print the content of the second chunk before freeing it
    printf("Second Chunk Content: %s\n", secondChunk);

    // Free the second chunk
    free(secondChunk);

    return EXIT_SUCCESS;
}