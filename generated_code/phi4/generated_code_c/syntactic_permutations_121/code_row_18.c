#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 100; // Size of each memory chunk

    // Allocate two chunks of memory
    char *chunk1 = (char *)malloc(size);
    if (!chunk1) {
        perror("Failed to allocate memory for chunk1");
        return EXIT_FAILURE;
    }
    
    char *chunk2 = (char *)malloc(size);
    if (!chunk2) {
        free(chunk1); // Free the first chunk before exiting
        perror("Failed to allocate memory for chunk2");
        return EXIT_FAILURE;
    }

    // Initialize the contents of the first chunk with some data
    snprintf(chunk1, size, "This is the content of the first memory chunk.");

    // Copy the contents of the first chunk into the second chunk
    strcpy(chunk2, chunk1);

    // Print and free the memory allocated to the first chunk
    printf("Contents of the first chunk: %s\n", chunk1);
    free(chunk1);

    // Print and free the memory allocated to the second chunk
    printf("Contents of the second chunk: %s\n", chunk2);
    free(chunk2);

    return EXIT_SUCCESS;
}