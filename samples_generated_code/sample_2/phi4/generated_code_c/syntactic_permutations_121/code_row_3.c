#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory
    char *first_chunk = (char *)malloc(10);
    char *second_chunk = (char *)malloc(10);

    if (first_chunk == NULL || second_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Copy contents into the first chunk
    strcpy(first_chunk, "Hello");

    // Copy contents of the first chunk to the second chunk
    strcpy(second_chunk, first_chunk);

    // Print the contents of the second chunk
    printf("Second Chunk: %s\n", second_chunk);

    // Free the memory allocated for the first chunk
    free(first_chunk);
    
    // Print the contents of the second chunk again
    printf("Second Chunk after freeing first: %s\n", second_chunk);

    // Free the memory allocated to the second chunk
    free(second_chunk);

    return 0;
}