#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 10;
    
    // Allocate first chunk of memory
    char *first_chunk = (char *)malloc(size);
    if (!first_chunk) {
        perror("Failed to allocate memory for the first chunk");
        return EXIT_FAILURE;
    }

    // Initialize first chunk with some data
    strcpy(first_chunk, "HelloWorld");

    // Allocate second chunk of memory
    char *second_chunk = (char *)malloc(size);
    if (!second_chunk) {
        free(first_chunk);
        perror("Failed to allocate memory for the second chunk");
        return EXIT_FAILURE;
    }

    // Copy contents from first chunk to second chunk
    memcpy(second_chunk, first_chunk, size);

    // Print contents of second chunk
    printf("%s\n", second_chunk);

    // Free allocated memory
    free(first_chunk);
    free(second_chunk);

    return 0;
}