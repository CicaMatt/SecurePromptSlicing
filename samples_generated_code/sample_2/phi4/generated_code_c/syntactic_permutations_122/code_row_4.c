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
        free(chunk1); // Free the first chunk before exiting
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Fill the first chunk with some data
    for (int i = 0; i < 10; ++i) {
        chunk1[i] = 'A' + i;
    }

    // Copy contents of the first chunk to the second chunk
    memcpy(chunk2, chunk1, 10);
    
    // Print the copied data in the second chunk
    printf("Copied Data: %s\n", chunk2);

    // Free the first chunk
    free(chunk1);

    // Free the second chunk
    free(chunk2);

    return 0;
}