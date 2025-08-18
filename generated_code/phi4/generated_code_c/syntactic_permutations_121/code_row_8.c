#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory
    char *chunk1 = (char *)malloc(10);
    char *chunk2 = (char *)malloc(10);

    if (!chunk1 || !chunk2) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Copy contents from first chunk to second chunk
    strcpy(chunk1, "Hello");
    strcpy(chunk2, chunk1);

    // Print contents of the second chunk
    printf("Contents of the second chunk: %s\n", chunk2);

    // Free the memory allocated to the first chunk
    free(chunk1);

    // Print contents of the second chunk after freeing the first chunk
    printf("Contents of the second chunk after freeing first: %s\n", chunk2);

    // Free the memory allocated to the second chunk
    free(chunk2);

    return 0;
}