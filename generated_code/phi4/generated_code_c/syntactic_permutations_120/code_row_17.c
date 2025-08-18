#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size1 = 10;
    size_t size2 = 15;

    // Allocate two chunks of memory
    char *chunk1 = (char *)malloc(size1);
    if (!chunk1) {
        perror("Failed to allocate chunk1");
        return EXIT_FAILURE;
    }

    char *chunk2 = (char *)malloc(size2);
    if (!chunk2) {
        free(chunk1);
        perror("Failed to allocate chunk2");
        return EXIT_FAILURE;
    }

    // Initialize the first chunk with some data
    strcpy(chunk1, "Hello");

    // Copy contents of the first chunk into the second chunk
    strncpy(chunk2, chunk1, size2 - 1);
    chunk2[size2 - 1] = '\0'; // Ensure null termination

    // Print the contents of the second chunk
    printf("Contents of the second chunk: %s\n", chunk2);

    // Free allocated memory
    free(chunk1);
    free(chunk2);

    return EXIT_SUCCESS;
}