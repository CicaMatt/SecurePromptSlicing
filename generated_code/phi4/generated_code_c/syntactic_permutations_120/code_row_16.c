#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory, each 100 bytes
    char *first_chunk = (char *)malloc(100);
    char *second_chunk = (char *)malloc(100);

    if (!first_chunk || !second_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the first chunk with some data
    strcpy(first_chunk, "Hello from the first memory chunk!");

    // Copy contents of the first chunk to the second chunk
    memcpy(second_chunk, first_chunk, strlen(first_chunk) + 1);

    // Print the contents of the second chunk
    printf("Contents of the second chunk: %s\n", second_chunk);

    // Free allocated memory
    free(first_chunk);
    free(second_chunk);

    return 0;
}