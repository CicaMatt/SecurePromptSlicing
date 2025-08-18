#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t length = 10; // Example length for demonstration purposes

    // Allocate memory for two chunks
    char *first_chunk = (char *)malloc(length * sizeof(char));
    if (!first_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    char *second_chunk = (char *)malloc(length * sizeof(char));
    if (!second_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        return 1;
    }

    // Initialize the first chunk with some data
    for (size_t i = 0; i < length - 1; ++i) {
        first_chunk[i] = 'a' + (i % 26); // Fill with 'a', 'b', ..., 'z'
    }
    first_chunk[length - 1] = '\0'; // Null-terminate the string

    // Copy contents of the first chunk into the second chunk
    memcpy(second_chunk, first_chunk, length);

    // Print the contents of the second chunk
    printf("Contents of the second chunk: %s\n", second_chunk);

    // Free allocated memory
    free(first_chunk);
    free(second_chunk);

    return 0;
}