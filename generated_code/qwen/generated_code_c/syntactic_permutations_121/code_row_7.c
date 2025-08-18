#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk;
    char *second_chunk;

    // Allocate memory for first chunk
    first_chunk = (char *)malloc(10 * sizeof(char));
    if (first_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize first chunk with some data
    strcpy(first_chunk, "Hello");

    // Allocate memory for second chunk
    second_chunk = (char *)malloc(10 * sizeof(char));
    if (second_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        return 1;
    }

    // Copy contents of first chunk to second chunk
    strcpy(second_chunk, first_chunk);

    // Print contents of second chunk
    printf("Contents of second chunk: %s\n", second_chunk);

    // Free memory allocated to first chunk
    free(first_chunk);

    // Print contents of second chunk again
    printf("Contents of second chunk after freeing first chunk: %s\n", second_chunk);

    // Free memory allocated to second chunk
    free(second_chunk);

    return 0;
}