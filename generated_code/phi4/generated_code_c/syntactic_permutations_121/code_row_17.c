#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t length = 10;
    
    // Allocate two chunks of memory
    char *chunk1 = (char *)malloc(length * sizeof(char));
    if (chunk1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    char *chunk2 = (char *)malloc(length * sizeof(char));
    if (chunk2 == NULL) {
        free(chunk1);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Initialize the first chunk with some data
    for (size_t i = 0; i < length - 1; ++i) {
        chunk1[i] = 'A' + (char)i;
    }
    chunk1[length - 1] = '\0';

    // Copy contents of first chunk to second chunk
    strcpy(chunk2, chunk1);

    // Print the contents of the second chunk
    printf("Contents of second chunk: %s\n", chunk2);

    // Free the memory allocated for the first chunk
    free(chunk1);
    
    // Print the contents of the second chunk again
    printf("After freeing first chunk, contents of second chunk: %s\n", chunk2);

    // Free the memory allocated to the second chunk
    free(chunk2);

    return 0;
}