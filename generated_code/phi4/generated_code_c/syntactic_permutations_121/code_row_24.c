#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate first chunk of memory and initialize it
    char *first_chunk = (char *)malloc(10 * sizeof(char));
    if (!first_chunk) {
        perror("Failed to allocate memory");
        return 1;
    }
    
    strcpy(first_chunk, "Hello");

    // Allocate second chunk of memory
    char *second_chunk = (char *)malloc(10 * sizeof(char));
    if (!second_chunk) {
        perror("Failed to allocate memory");
        free(first_chunk);
        return 1;
    }

    // Copy contents from the first chunk to the second chunk
    strcpy(second_chunk, first_chunk);

    // Print the contents of the second chunk
    printf("Contents of second chunk: %s\n", second_chunk);

    // Free the memory allocated for the first chunk
    free(first_chunk);
    
    // Attempt to print the contents of the second chunk after freeing the first chunk
    printf("After freeing the first chunk, contents of second chunk: %s\n", second_chunk);

    // Free the memory allocated for the second chunk
    free(second_chunk);

    return 0;
}