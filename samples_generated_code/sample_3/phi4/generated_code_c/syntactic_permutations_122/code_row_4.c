#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory, each of size 10
    char *chunk1 = (char *)malloc(10);
    char *chunk2 = (char *)malloc(10);

    if (!chunk1 || !chunk2) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    // Initialize the first chunk with some data
    strcpy(chunk1, "abcdefghij");

    // Copy contents of the first chunk to the second chunk
    memcpy(chunk2, chunk1, 10);

    // Free the first chunk
    free(chunk1);

    // Print the contents of the second chunk to verify
    printf("Contents of the second chunk: %s\n", chunk2);

    // Free the second chunk
    free(chunk2);

    return EXIT_SUCCESS;
}