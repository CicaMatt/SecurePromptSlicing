#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 10;
    
    // Allocate two chunks of memory
    char *chunk1 = (char *)malloc(size);
    if (!chunk1) {
        perror("Failed to allocate chunk1");
        return EXIT_FAILURE;
    }
    
    char *chunk2 = (char *)malloc(size);
    if (!chunk2) {
        free(chunk1); // Free the first chunk on error
        perror("Failed to allocate chunk2");
        return EXIT_FAILURE;
    }

    // Initialize contents of the first chunk for demonstration purposes
    strcpy(chunk1, "Hello");

    // Copy contents of the first chunk into the second chunk
    memcpy(chunk2, chunk1, size);

    printf("Contents of chunk2: %s\n", chunk2);

    // Free the first chunk
    free(chunk1);

    // Free the second chunk
    free(chunk2);
    
    return 0;
}