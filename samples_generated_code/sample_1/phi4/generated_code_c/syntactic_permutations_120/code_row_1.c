#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Size of each chunk
    size_t size = 10;

    // Allocate two chunks of memory
    char *chunk1 = (char *)malloc(size);
    if (chunk1 == NULL) {
        fprintf(stderr, "Memory allocation failed for chunk1\n");
        return 1;
    }
    
    char *chunk2 = (char *)malloc(size);
    if (chunk2 == NULL) {
        fprintf(stderr, "Memory allocation failed for chunk2\n");
        free(chunk1); // Free previously allocated memory
        return 1;
    }

    // Initialize the first chunk with some data
    strcpy(chunk1, "HelloWorld");

    // Copy contents of the first chunk into the second chunk
    memcpy(chunk2, chunk1, size);

    // Print the contents of the second chunk
    printf("Contents of the second chunk: %s\n", chunk2);

    // Free allocated memory
    free(chunk1);
    free(chunk2);

    return 0;
}