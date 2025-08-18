#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate first chunk of memory with 20 bytes
    char *first_chunk = (char *)malloc(20);
    if (first_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the contents of the first chunk
    strcpy(first_chunk, "Hello, World!");

    // Allocate second chunk of memory with enough space for the same size as first_chunk
    char *second_chunk = (char *)malloc(strlen(first_chunk) + 1);
    if (second_chunk == NULL) {
        free(first_chunk); // Free previously allocated memory
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Copy contents from the first chunk to the second chunk
    strcpy(second_chunk, first_chunk);

    // Print the contents of the second chunk
    printf("%s\n", second_chunk);

    // Free allocated memory
    free(first_chunk);
    free(second_chunk);

    return 0;
}