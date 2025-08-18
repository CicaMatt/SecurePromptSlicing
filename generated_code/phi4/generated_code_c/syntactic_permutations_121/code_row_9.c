#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const int size = 10;
    
    // Allocate two chunks of memory
    char *first_chunk = (char *)malloc(size);
    if (!first_chunk) {
        perror("Failed to allocate first chunk");
        return EXIT_FAILURE;
    }
    char *second_chunk = (char *)malloc(size);
    if (!second_chunk) {
        perror("Failed to allocate second chunk");
        free(first_chunk);
        return EXIT_FAILURE;
    }

    // Initialize and copy contents from the first chunk into the second
    for(int i = 0; i < size - 1; i++) {
        first_chunk[i] = 'A' + i; 
    }
    first_chunk[size - 1] = '\0';

    strcpy(second_chunk, first_chunk);

    // Print contents of the second chunk
    printf("Contents of second chunk: %s\n", second_chunk);

    // Free memory allocated to the first chunk
    free(first_chunk);
    
    // Print contents of the second chunk again after freeing first chunk
    printf("Contents of second chunk after freeing first chunk: %s\n", second_chunk);

    // Free memory allocated to the second chunk
    free(second_chunk);

    return 0;
}