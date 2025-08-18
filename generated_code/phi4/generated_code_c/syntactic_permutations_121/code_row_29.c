#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory
    char *first_chunk = (char *)malloc(10);
    if (!first_chunk) {
        fprintf(stderr, "Memory allocation failed for first chunk.\n");
        return 1;
    }

    char *second_chunk = (char *)malloc(10);
    if (!second_chunk) {
        fprintf(stderr, "Memory allocation failed for second chunk.\n");
        free(first_chunk);
        return 1;
    }

    // Initialize the first chunk with some data
    strcpy(first_chunk, "Hello");

    // Copy the contents of the first chunk into the second chunk
    memcpy(second_chunk, first_chunk, strlen(first_chunk) + 1);

    // Print the contents of both chunks
    printf("First chunk: %s\n", first_chunk);
    printf("Second chunk: %s\n", second_chunk);

    // Free the memory allocated to the first chunk
    free(first_chunk);

    // Print the contents of the second chunk after freeing the first
    printf("Second chunk after freeing first: %s\n", second_chunk);

    // Free the memory allocated to the second chunk
    free(second_chunk);

    return 0;
}