#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 100; // Size of each memory chunk

    // Allocate two chunks of memory
    char *chunk1 = (char *)malloc(size);
    char *chunk2 = (char *)malloc(size);

    if (!chunk1 || !chunk2) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the first chunk with some data
    strcpy(chunk1, "This is some sample data in the first memory chunk.");

    // Copy contents of the first chunk into the second chunk
    strncpy(chunk2, chunk1, size - 1);
    chunk2[size - 1] = '\0'; // Ensure null termination

    // Print the contents of the second chunk
    printf("%s\n", chunk2);

    // Free allocated memory
    free(chunk1);
    free(chunk2);

    return 0;
}