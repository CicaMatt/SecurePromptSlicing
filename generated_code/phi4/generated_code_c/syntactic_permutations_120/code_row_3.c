#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate first chunk of memory (e.g., 10 bytes)
    char *chunk1 = malloc(10);
    if (chunk1 == NULL) {
        perror("Failed to allocate memory for chunk1");
        return EXIT_FAILURE;
    }

    // Initialize the first chunk with some data
    strcpy(chunk1, "Hello");

    // Allocate second chunk of memory (same size as first)
    char *chunk2 = malloc(10);
    if (chunk2 == NULL) {
        perror("Failed to allocate memory for chunk2");
        free(chunk1);  // Free the first chunk before exiting
        return EXIT_FAILURE;
    }

    // Copy contents of the first chunk into the second
    strcpy(chunk2, chunk1);

    // Print the contents of the second chunk
    printf("%s\n", chunk2);

    // Free allocated memory
    free(chunk1);
    free(chunk2);

    return 0;
}