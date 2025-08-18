#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate first chunk of memory and initialize it with some data
    size_t len = 10;
    char *first_chunk = (char *)malloc(len * sizeof(char));
    
    if (!first_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(first_chunk, "abcdefghij");

    // Allocate second chunk of memory
    char *second_chunk = (char *)malloc((len + 1) * sizeof(char)); // Extra for null terminator

    if (!second_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        return 1;
    }

    // Copy contents from the first chunk to the second
    strcpy(second_chunk, first_chunk);

    // Print the contents of the second chunk
    printf("Contents of the second chunk: %s\n", second_chunk);

    // Free the memory allocated to the first chunk
    free(first_chunk);

    // Print the contents of the second chunk again after freeing the first
    printf("Contents of the second chunk (after freeing first): %s\n", second_chunk);

    // Free the memory allocated to the second chunk
    free(second_chunk);

    return 0;
}