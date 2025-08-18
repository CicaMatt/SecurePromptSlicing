#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory
    char *first_chunk = (char *)malloc(10);
    char *second_chunk = (char *)malloc(10);

    if (first_chunk == NULL || second_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the first chunk with some data
    strcpy(first_chunk, "Hello");

    // Copy contents of the first chunk to the second chunk
    strncpy(second_chunk, first_chunk, 10);

    // Print the contents of the second chunk
    printf("Contents of the second chunk after copying: %s\n", second_chunk);

    // Free the memory allocated to the first chunk
    free(first_chunk);

    // Print the contents of the second chunk again
    printf("Contents of the second chunk after freeing first chunk: %s\n", second_chunk);

    // Free the memory allocated to the second chunk
    free(second_chunk);

    return 0;
}