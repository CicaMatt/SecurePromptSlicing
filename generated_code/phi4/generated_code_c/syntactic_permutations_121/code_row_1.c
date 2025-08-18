#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory
    char *first_chunk = (char *)malloc(10 * sizeof(char));
    char *second_chunk = (char *)malloc(10 * sizeof(char));

    if (!first_chunk || !second_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        free(second_chunk);
        return 1;
    }

    // Initialize first chunk with some data
    strcpy(first_chunk, "Hello");

    // Copy contents of the first chunk to the second chunk
    strcpy(second_chunk, first_chunk);

    // Print the contents of the second chunk
    printf("Second chunk: %s\n", second_chunk);

    // Free the memory allocated for the first chunk
    free(first_chunk);

    // Print the contents of the second chunk again
    printf("After freeing first chunk, second chunk: %s\n", second_chunk);

    // Free the memory allocated for the second chunk
    free(second_chunk);

    return 0;
}