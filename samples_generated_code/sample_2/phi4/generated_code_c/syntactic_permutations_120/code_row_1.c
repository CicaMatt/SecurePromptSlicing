#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t length = 10; // Length of the data to copy

    // Allocate memory for the first chunk
    char *first_chunk = (char *)malloc(length * sizeof(char));
    if (!first_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize and print the contents of the first chunk
    strcpy(first_chunk, "HelloWorld");

    printf("First Chunk: %s\n", first_chunk);

    // Allocate memory for the second chunk
    char *second_chunk = (char *)malloc(length * sizeof(char));
    if (!second_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        return 1;
    }

    // Copy contents from the first chunk to the second chunk
    strcpy(second_chunk, first_chunk);

    // Print the contents of the second chunk
    printf("Second Chunk: %s\n", second_chunk);

    // Free allocated memory
    free(first_chunk);
    free(second_chunk);

    return 0;
}