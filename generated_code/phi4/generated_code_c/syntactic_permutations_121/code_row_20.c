#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t n = 10;
    char *first_chunk = (char *)malloc(n);
    if (!first_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the first chunk with some values
    for (size_t i = 0; i < n - 1; ++i) {
        first_chunk[i] = 'A' + i;
    }
    first_chunk[n - 1] = '\0';

    // Allocate second chunk and copy contents of first_chunk into it
    char *second_chunk = (char *)malloc(n);
    if (!second_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        return 1;
    }

    memcpy(second_chunk, first_chunk, n);

    // Print the contents of the second chunk
    printf("Second chunk: %s\n", second_chunk);

    // Free the memory allocated to the first chunk
    free(first_chunk);

    // Print the contents of the second chunk again
    printf("Second chunk after freeing first: %s\n", second_chunk);

    // Free the memory allocated to the second chunk
    free(second_chunk);

    return 0;
}