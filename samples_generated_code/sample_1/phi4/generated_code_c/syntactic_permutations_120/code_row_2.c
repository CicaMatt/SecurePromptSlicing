#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 10;
    
    // Allocate two chunks of memory
    char *chunk1 = (char *)malloc(size * sizeof(char));
    if (chunk1 == NULL) {
        perror("Failed to allocate memory for chunk1");
        return EXIT_FAILURE;
    }

    char *chunk2 = (char *)malloc(size * sizeof(char));
    if (chunk2 == null) {
        free(chunk1);
        perror("Failed to allocate memory for chunk2");
        return EXIT_FAILURE;
    }
    
    // Initialize the first chunk with some data
    strcpy(chunk1, "Hello");

    // Copy contents of the first chunk into the second chunk
    memcpy(chunk2, chunk1, size);

    // Print the contents of the second chunk
    printf("Contents of the second chunk: %s\n", chunk2);
    
    // Free allocated memory
    free(chunk1);
    free(chunk2);
    
    return EXIT_SUCCESS;
}