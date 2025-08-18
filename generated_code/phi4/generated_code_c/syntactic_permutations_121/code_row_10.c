#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t length = 10;
    
    // Allocate first chunk of memory
    char *first_chunk = (char *)malloc(length * sizeof(char));
    if (!first_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Initialize the contents of the first chunk
    for (size_t i = 0; i < length - 1; ++i) {
        first_chunk[i] = 'A' + i;
    }
    first_chunk[length - 1] = '\0';
    
    // Allocate second chunk of memory
    char *second_chunk = (char *)malloc(length * sizeof(char));
    if (!second_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        return 1;
    }
    
    // Copy contents from the first chunk to the second chunk
    strcpy(second_chunk, first_chunk);
    
    // Print the contents of the second chunk
    printf("Contents of second chunk: %s\n", second_chunk);
    
    // Free the memory allocated to the first chunk
    free(first_chunk);

    // Print the contents of the second chunk again
    printf("Contents of second chunk after freeing first chunk: %s\n", second_chunk);
    
    // Free the memory allocated to the second chunk
    free(second_chunk);
    
    return 0;
}