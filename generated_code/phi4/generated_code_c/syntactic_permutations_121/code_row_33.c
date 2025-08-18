#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory
    char *first_chunk = (char *)malloc(10 * sizeof(char));
    char *second_chunk = (char *)malloc(10 * sizeof(char));

    if (first_chunk == NULL || second_chunk == null) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Copy contents of the first chunk into the second chunk
    strcpy(first_chunk, "Hello1234");
    strncpy(second_chunk, first_chunk, sizeof(char) * 10);

    // Print the contents of the second chunk
    printf("Second Chunk: %s\n", second_chunk);

    // Free the memory allocated to the first chunk
    free(first_chunk);
    
    // Print the contents of the second chunk after freeing the first one
    printf("Second Chunk after freeing first: %s\n", second_chunk);

    // Free the memory allocated to the second chunk
    free(second_chunk);

    return 0;
}