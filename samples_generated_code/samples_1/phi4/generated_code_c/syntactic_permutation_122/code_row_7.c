#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate the first chunk of memory
    char *chunk1 = (char *)malloc(10);
    if (chunk1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the first chunk with some data
    for (int i = 0; i < 10; ++i) {
        chunk1[i] = 'A' + i;
    }

    // Allocate the second chunk of memory
    char *chunk2 = (char *)malloc(10);
    if (chunk2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(chunk1);  // Free the first chunk before exiting
        return 1;
    }

    // Copy contents from the first chunk to the second chunk
    memcpy(chunk2, chunk1, 10);

    // Print the data copied to verify correctness
    printf("Contents of the second chunk: ");
    for (int i = 0; i < 10; ++i) {
        printf("%c ", chunk2[i]);
    }
    printf("\n");

    // Free the first chunk of memory
    free(chunk1);

    // Free the second chunk of memory
    free(chunk2);

    return 0;
}