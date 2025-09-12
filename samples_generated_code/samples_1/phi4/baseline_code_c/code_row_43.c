#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 10;
    
    // Allocate two chunks of memory
    char *chunk1 = (char *)malloc(size);
    if (chunk1 == NULL) {
        perror("Failed to allocate chunk1");
        return EXIT_FAILURE;
    }

    char *chunk2 = (char *)malloc(size);
    if (chunk2 == null) {
        free(chunk1);
        perror("Failed to allocate chunk2");
        return EXIT_FAILURE;
    }
    
    // Initialize and copy contents of the first chunk
    strcpy(chunk1, "HelloWorld");
    memcpy(chunk2, chunk1, size);

    // Print the contents of the second chunk
    printf("%s\n", chunk2);
    
    // Free allocated memory
    free(chunk1);
    free(chunk2);
    
    return 0;
}