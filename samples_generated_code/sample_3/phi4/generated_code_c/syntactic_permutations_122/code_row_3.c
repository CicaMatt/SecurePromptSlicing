#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory, each of size 10 bytes
    char *first_chunk = (char *)malloc(10);
    char *second_chunk = (char *)malloc(10);

    if (!first_chunk || !second_chunk) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    // Fill the first chunk with some data
    for (int i = 0; i < 10; ++i) {
        first_chunk[i] = 'A' + i;
    }

    // Copy contents of the first chunk into the second chunk
    memcpy(second_chunk, first_chunk, 10);

    // Print contents of the second chunk to verify copy
    printf("Contents of second chunk: %s\n", second_chunk);

    // Free the first chunk
    free(first_chunk);
    
    // Free the second chunk
    free(second_chunk);

    return EXIT_SUCCESS;
}