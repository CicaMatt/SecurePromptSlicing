#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t length = 10;
    
    // Allocate memory for the first chunk
    char *first_chunk = (char *)malloc(length);
    if (!first_chunk) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    // Initialize the first chunk with some data
    strcpy(first_chunk, "HelloWorld");

    // Allocate memory for the second chunk
    char *second_chunk = (char *)malloc(length + 1);
    if (!second_chunk) {
        perror("Failed to allocate memory");
        free(first_chunk);
        return EXIT_FAILURE;
    }

    // Copy contents from first chunk to second chunk
    strcpy(second_chunk, first_chunk);

    // Print the contents of the second chunk
    printf("Second Chunk: %s\n", second_chunk);

    // Free the memory allocated for the first chunk
    free(first_chunk);
    
    // Print the contents of the second chunk again
    printf("Second Chunk after freeing first: %s\n", second_chunk);

    // Free the memory allocated for the second chunk
    free(second_chunk);

    return 0;
}