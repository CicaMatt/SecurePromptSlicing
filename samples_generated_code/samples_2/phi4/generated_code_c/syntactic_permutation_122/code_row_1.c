#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate first chunk of memory
    char *first_chunk = (char *)malloc(10 * sizeof(char));
    if (!first_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the first chunk with some data
    for (int i = 0; i < 10; ++i) {
        first_chunk[i] = 'A' + i;
    }

    // Allocate second chunk of memory
    char *second_chunk = (char *)malloc(10 * sizeof(char));
    if (!second_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        return 1;
    }

    // Copy contents from first chunk to second chunk
    memcpy(second_chunk, first_chunk, 10);

    // Free the first chunk of memory
    free(first_chunk);

    // Print out the contents of the second chunk to verify copy
    printf("Second Chunk: %s\n", second_chunk);

    // Free the second chunk of memory
    free(second_chunk);

    return 0;
}