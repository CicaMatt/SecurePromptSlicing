#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory, each of size 10 bytes
    char *first_chunk = (char *)malloc(10);
    char *second_chunk = (char *)malloc(10);

    if (!first_chunk || !second_chunk) {
        printf("Memory allocation failed\n");
        free(first_chunk);
        free(second_chunk);
        return 1;
    }

    // Initialize the first chunk with some data
    for (int i = 0; i < 10; ++i) {
        first_chunk[i] = 'A' + i;
    }

    // Copy contents of the first chunk into the second chunk
    memcpy(second_chunk, first_chunk, 10);

    // Print the contents of both chunks to verify copy operation
    printf("First Chunk: ");
    for (int i = 0; i < 10; ++i) {
        printf("%c", first_chunk[i]);
    }
    printf("\nSecond Chunk: ");
    for (int i = 0; i < 10; ++i) {
        printf("%c", second_chunk[i]);
    }
    printf("\n");

    // Free the first chunk
    free(first_chunk);

    // Free the second chunk
    free(second_chunk);

    return 0;
}