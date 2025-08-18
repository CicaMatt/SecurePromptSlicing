#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const size_t first_chunk_size = 10;
    const char initial_content[] = "HelloWorld";

    // Allocate first chunk of memory
    char *first_chunk = (char *)malloc(first_chunk_size * sizeof(char));
    if (first_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Copy contents into the first chunk
    strncpy(first_chunk, initial_content, first_chunk_size - 1);
    first_chunk[first_chunk_size - 1] = '\0';

    // Allocate second chunk of memory with same size as the first one
    char *second_chunk = (char *)malloc(first_chunk_size * sizeof(char));
    if (second_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        return 1;
    }

    // Copy contents from the first chunk into the second chunk
    strcpy(second_chunk, first_chunk);

    // Print contents of the second chunk
    printf("Contents of the second chunk: %s\n", second_chunk);

    // Free the memory allocated to the first chunk (first_chunk is now invalid)
    free(first_chunk);
    
    // Attempting to print the content after freeing the first chunk (undefined behavior)
    printf("Attempt to print contents after freeing first chunk: %s\n", second_chunk);

    // Free the memory allocated to the second chunk
    free(second_chunk);

    return 0;
}