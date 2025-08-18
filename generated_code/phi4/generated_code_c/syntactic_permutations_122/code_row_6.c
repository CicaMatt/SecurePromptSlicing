#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate memory for two chunks, each of size 10 bytes
    char *chunk1 = (char *)malloc(10);
    char *chunk2 = (char *)malloc(10);

    if (chunk1 == NULL || chunk2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Initialize the first chunk with some data
    for (int i = 0; i < 10; ++i) {
        chunk1[i] = 'A' + i;
    }
    
    // Copy contents of the first chunk into the second chunk
    memcpy(chunk2, chunk1, 10);

    // Free the first chunk
    free(chunk1);
    
    // Output the contents of the second chunk to verify copying
    for (int i = 0; i < 10; ++i) {
        printf("%c", chunk2[i]);
    }
    printf("\n");

    // Free the second chunk
    free(chunk2);

    return EXIT_SUCCESS;
}