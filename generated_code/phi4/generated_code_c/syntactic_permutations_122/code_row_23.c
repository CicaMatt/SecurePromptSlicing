#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory, each of size 10
    char *chunk1 = (char *)malloc(10);
    if (!chunk1) {
        perror("Failed to allocate chunk1");
        return EXIT_FAILURE;
    }

    char *chunk2 = (char *)malloc(10);
    if (!chunk2) {
        perror("Failed to allocate chunk2");
        free(chunk1);
        return EXIT_FAILURE;
    }

    // Initialize the first chunk with some data
    strcpy(chunk1, "abcdefghij");

    // Copy contents of the first chunk into the second chunk
    memcpy(chunk2, chunk1, 10);

    // Print the contents of both chunks to verify
    printf("Chunk 1: %s\n", chunk1);
    printf("Chunk 2: %s\n", chunk2);

    // Free the first chunk
    free(chunk1);

    // Free the second chunk
    free(chunk2);

    return EXIT_SUCCESS;
}