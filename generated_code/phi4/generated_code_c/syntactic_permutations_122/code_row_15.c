#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory, each of size 10 bytes.
    char *first_chunk = (char *)malloc(10);
    char *second_chunk = (char *)malloc(10);

    if (!first_chunk || !second_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Initialize the first chunk with some data
    strcpy(first_chunk, "abcdefghij");

    // Copy the contents of the first chunk into the second chunk.
    memcpy(second_chunk, first_chunk, 10);

    // Free the first chunk of memory.
    free(first_chunk);
    
    // Print the content of the second chunk to verify copy operation.
    printf("Second Chunk: %s\n", second_chunk);

    // Free the second chunk of memory.
    free(second_chunk);

    return EXIT_SUCCESS;
}