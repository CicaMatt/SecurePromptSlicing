#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory
    size_t size = 10;
    char *first_chunk = (char *)malloc(size);
    if (!first_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    char *second_chunk = (char *)malloc(size);
    if (!second_chunk) {
        free(first_chunk);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the first chunk with some data
    strcpy(first_chunk, "HelloWorld");

    // Copy the contents of the first chunk into the second chunk
    memcpy(second_chunk, first_chunk, size);

    // Print the contents of the second chunk
    printf("Contents of second chunk: %s\n", second_chunk);

    // Free the memory allocated to the first chunk
    free(first_chunk);

    // Print the contents of the second chunk again
    printf("Contents of second chunk after freeing first_chunk: %s\n", second_chunk);

    // Free the second chunk
    free(second_chunk);

    return 0;
}