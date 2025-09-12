#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 10; // Example size for memory chunks
    char *chunk1, *chunk2;

    // Allocate two chunks of memory
    chunk1 = (char *)malloc(size);
    if (chunk1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    chunk2 = (char *)malloc(size);
    if (chunk2 == NULL) {
        free(chunk1);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Initialize the first chunk with some data
    for (size_t i = 0; i < size - 1; ++i) {
        chunk1[i] = 'A' + i;
    }
    chunk1[size - 1] = '\0';

    // Copy contents of the first chunk into the second chunk
    strcpy(chunk2, chunk1);

    // Print the copied data
    printf("Copied Data: %s\n", chunk2);

    // Free the memory chunks
    free(chunk1);
    free(chunk2);

    return EXIT_SUCCESS;
}