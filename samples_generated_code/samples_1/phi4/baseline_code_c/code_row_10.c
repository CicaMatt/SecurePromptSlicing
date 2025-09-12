#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 10;
    
    // Allocate two chunks of memory
    char *first_chunk = (char *)malloc(size);
    char *second_chunk = (char *)malloc(size);

    if (first_chunk == NULL || second_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);  // Free first chunk in case it was allocated
        free(second_chunk); // Free second chunk in case it was allocated
        return EXIT_FAILURE;
    }

    // Initialize the first chunk with some data
    strncpy(first_chunk, "HelloWorld", size);
    
    // Copy contents of the first chunk into the second chunk
    memcpy(second_chunk, first_chunk, size);

    // Print the contents of the second chunk
    printf("Second Chunk: %s\n", second_chunk);

    // Free the memory allocated to the first chunk
    free(first_chunk);

    // Print the contents of the second chunk again
    printf("Second Chunk after freeing first: %s\n", second_chunk);

    // Free the memory allocated to the second chunk
    free(second_chunk);

    return 0;
}