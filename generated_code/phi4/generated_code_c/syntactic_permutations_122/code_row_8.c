#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 100;
    
    // Allocate two chunks of memory
    char *chunk1 = (char *)malloc(size);
    if (chunk1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    char *chunk2 = (char *)malloc(size);
    if (chunk2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(chunk1);
        return 1;
    }

    // Initialize the first chunk with some data
    for (size_t i = 0; i < size; ++i) {
        chunk1[i] = 'A' + (i % 26); // Fill with letters A-Z repeatedly
    }
    
    // Copy contents of the first chunk into the second chunk
    memcpy(chunk2, chunk1, size);

    // Free the first chunk
    free(chunk1);
    
    // Use the second chunk (e.g., print its contents)
    for (size_t i = 0; i < size; ++i) {
        putchar(chunk2[i]);
    }
    putchar('\n');

    // Free the second chunk
    free(chunk2);

    return 0;
}