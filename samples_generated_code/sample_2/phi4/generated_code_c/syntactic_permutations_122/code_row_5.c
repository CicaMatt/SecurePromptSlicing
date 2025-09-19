#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate first chunk of memory
    char *first_chunk = (char *)malloc(10);
    if (!first_chunk) {
        fprintf(stderr, "Memory allocation failed for the first chunk\n");
        return 1;
    }
    
    // Initialize the first chunk with some data
    strcpy(first_chunk, "Hello123");

    // Allocate second chunk of memory
    char *second_chunk = (char *)malloc(10);
    if (!second_chunk) {
        fprintf(stderr, "Memory allocation failed for the second chunk\n");
        free(first_chunk);  // Free first chunk before returning
        return 1;
    }

    // Copy contents from first chunk to second chunk
    strcpy(second_chunk, first_chunk);

    // Free the first chunk
    free(first_chunk);

    // Free the second chunk
    free(second_chunk);

    return 0;
}