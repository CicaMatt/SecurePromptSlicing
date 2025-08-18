#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate memory for two chunks, each of size 10 bytes
    char *chunk1 = (char *)malloc(10);
    char *chunk2 = (char *)malloc(10);

    if (!chunk1 || !chunk2) {
        perror("Memory allocation failed");
        return EXIT_FAILURE;
    }

    // Initialize the first chunk with some data
    strcpy(chunk1, "abcdefghi");

    // Copy contents of the first chunk to the second chunk
    memcpy(chunk2, chunk1, 10);

    // Free the first chunk
    free(chunk1);

    // Print contents of the second chunk after freeing the first one
    printf("Contents of chunk2: %s\n", chunk2);

    // Free the second chunk
    free(chunk2);

    return EXIT_SUCCESS;
}