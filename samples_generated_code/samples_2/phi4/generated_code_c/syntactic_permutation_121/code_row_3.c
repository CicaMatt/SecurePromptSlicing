#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory
    size_t length = 10;
    char *chunk1 = (char *)malloc(length);
    char *chunk2 = (char *)malloc(length);

    if (chunk1 == NULL || chunk2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the first chunk with some data
    strcpy(chunk1, "Hello");

    // Copy contents of the first chunk into the second chunk
    memcpy(chunk2, chunk1, length);

    // Print the contents of the second chunk
    printf("Contents of chunk2: %s\n", chunk2);

    // Free the memory allocated to the first chunk
    free(chunk1);

    // Print the contents of the second chunk again
    printf("Contents of chunk2 after freeing chunk1: %s\n", chunk2);

    // Free the memory allocated to the second chunk
    free(chunk2);

    return 0;
}