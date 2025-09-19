#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t length = 10;
    
    // Allocate two chunks of memory
    char *chunk1 = (char *)malloc(length);
    if (!chunk1) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    char *chunk2 = (char *)malloc(length);
    if (!chunk2) {
        free(chunk1);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize first chunk with some data
    strcpy(chunk1, "HelloWorld");

    // Copy the contents of the first chunk into the second chunk
    memcpy(chunk2, chunk1, length);

    // Print the contents of the second chunk
    printf("Second chunk after copy: %s\n", chunk2);

    // Free the memory allocated to the first chunk
    free(chunk1);
    
    // Print the contents of the second chunk again
    printf("Second chunk after freeing first chunk: %s\n", chunk2);

    // Free the memory allocated to the second chunk
    free(chunk2);

    return 0;
}