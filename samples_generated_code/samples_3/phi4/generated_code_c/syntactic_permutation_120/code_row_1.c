#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory
    int size = 10; // Define the size of each chunk
    char *chunk1 = (char *)malloc(size * sizeof(char));
    char *chunk2 = (char *)malloc(size * sizeof(char));

    if (!chunk1 || !chunk2) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    // Initialize the first chunk with some data
    strcpy(chunk1, "Hello");

    // Copy the contents of the first chunk into the second chunk
    memcpy(chunk2, chunk1, size);

    // Print the contents of the second chunk
    printf("Contents of the second chunk: %s\n", chunk2);

    // Free allocated memory
    free(chunk1);
    free(chunk2);

    return 0;
}