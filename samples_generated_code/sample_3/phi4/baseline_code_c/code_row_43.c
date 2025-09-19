#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size1 = 10; // Size of the first memory chunk
    char *chunk1 = (char *)malloc(size1);
    
    if (!chunk1) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(chunk1, "Hello"); // Copy contents to the first chunk

    size_t size2 = 10; // Size of the second memory chunk
    char *chunk2 = (char *)malloc(size2);
    
    if (!chunk2) {
        fprintf(stderr, "Memory allocation failed\n");
        free(chunk1); // Free previously allocated memory before exiting
        return 1;
    }

    memcpy(chunk2, chunk1, size1); // Copy contents from the first to the second chunk

    printf("Contents of the second chunk: %s\n", chunk2);

    free(chunk1);
    free(chunk2);

    return 0;
}