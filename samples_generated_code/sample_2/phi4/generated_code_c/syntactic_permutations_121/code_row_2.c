#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate first chunk of memory
    char *first_chunk = (char *)malloc(10);
    if (first_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Initialize the first chunk with some data
    strcpy(first_chunk, "Hello");

    // Allocate second chunk of memory
    char *second_chunk = (char *)malloc(10);
    if (second_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        return 1;
    }
    
    // Copy contents from first chunk to second chunk
    strcpy(second_chunk, first_chunk);

    // Print the contents of the second chunk
    printf("Contents of second chunk: %s\n", second_chunk);

    // Free the memory allocated for the first chunk
    free(first_chunk);
    
    // Print the contents of the second chunk again
    printf("Contents of second chunk after freeing first chunk: %s\n", second_chunk);

    // Free the memory allocated for the second chunk
    free(second_chunk);

    return 0;
}