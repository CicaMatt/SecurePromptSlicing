#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory, each of size 10 bytes
    char *chunk1 = (char *)malloc(10);
    if (!chunk1) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    char *chunk2 = (char *)malloc(10);
    if (!chunk2) {
        free(chunk1); // Free the first chunk if second fails
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Fill the first chunk with some data
    for (int i = 0; i < 10; ++i) {
        chunk1[i] = 'A' + i;
    }

    // Copy contents of the first chunk to the second chunk
    memcpy(chunk2, chunk1, 10);

    // Free the first chunk
    free(chunk1);
    
    // Print contents of the second chunk to verify copy
    printf("Contents of second chunk: ");
    for (int i = 0; i < 10; ++i) {
        printf("%c ", chunk2[i]);
    }
    printf("\n");

    // Free the second chunk
    free(chunk2);

    return EXIT_SUCCESS;
}