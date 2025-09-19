#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate first chunk of memory
    char *first_chunk = (char *)malloc(10);
    
    if (!first_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the first chunk with some data
    for (int i = 0; i < 10; ++i) {
        first_chunk[i] = 'A' + i;
    }
    
    // Allocate second chunk of memory
    char *second_chunk = (char *)malloc(10);

    if (!second_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        return 1;
    }

    // Copy contents from first chunk to second chunk
    memcpy(second_chunk, first_chunk, 10);

    // Free the first chunk
    free(first_chunk);

    // Print content of the second chunk for verification
    printf("Second Chunk: %s\n", second_chunk);

    // Free the second chunk
    free(second_chunk);

    return 0;
}