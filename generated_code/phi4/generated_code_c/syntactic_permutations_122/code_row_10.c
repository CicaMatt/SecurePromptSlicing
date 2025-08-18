#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 100; // Define the size for each memory chunk

    // Allocate two chunks of memory
    char *chunk1 = (char *)malloc(size);
    if (!chunk1) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    char *chunk2 = (char *)malloc(size);
    if (!chunk2) {
        free(chunk1); // Free the first chunk before exiting
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the contents of the first chunk
    for (size_t i = 0; i < size; ++i) {
        chunk1[i] = 'A' + (i % 26);
    }

    // Copy contents from the first chunk to the second chunk
    memcpy(chunk2, chunk1, size);

    // Free the first chunk of memory
    free(chunk1);

    // Free the second chunk of memory
    free(chunk2);

    return 0;
}