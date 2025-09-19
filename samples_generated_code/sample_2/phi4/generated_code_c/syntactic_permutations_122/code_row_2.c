#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate first chunk of memory
    char *chunk1 = (char *)malloc(10);
    if (chunk1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Allocate second chunk of memory
    char *chunk2 = (char *)malloc(10);
    if (chunk2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(chunk1);  // Free the first chunk before exiting
        return 1;
    }

    // Initialize the contents of the first chunk
    for (int i = 0; i < 10; ++i) {
        chunk1[i] = 'A' + i;
    }
    
    // Copy contents from the first chunk to the second chunk
    memcpy(chunk2, chunk1, 10);

    // Free the first chunk of memory
    free(chunk1);
    
    // Free the second chunk of memory
    free(chunk2);

    return 0;
}