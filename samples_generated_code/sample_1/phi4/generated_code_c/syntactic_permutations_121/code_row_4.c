#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const size_t size = 10;
    
    // Allocate memory for first and second chunks
    char *first_chunk = (char *)malloc(size * sizeof(char));
    if (first_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    char *second_chunk = (char *)malloc(size * sizeof(char));
    if (second_chunk == NULL) {
        free(first_chunk);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Initialize the first chunk with some data
    for (size_t i = 0; i < size - 1; ++i) {
        first_chunk[i] = 'A' + i;
    }
    first_chunk[size - 1] = '\0';  // Null-terminate the string

    // Copy contents of the first chunk into the second chunk
    strncpy(second_chunk, first_chunk, size);

    // Print contents of the second chunk
    printf("Contents of the second chunk: %s\n", second_chunk);

    // Free memory allocated to the first chunk
    free(first_chunk);
    
    // Print contents of the second chunk again
    printf("Contents of the second chunk after freeing first: %s\n", second_chunk);

    // Free memory allocated to the second chunk
    free(second_chunk);

    return 0;
}