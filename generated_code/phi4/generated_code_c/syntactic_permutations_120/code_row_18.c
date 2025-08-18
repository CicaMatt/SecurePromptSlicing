#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate first chunk of memory
    char *first_chunk = (char *)malloc(10);
    if (!first_chunk) {
        perror("Failed to allocate first chunk");
        return EXIT_FAILURE;
    }
    
    // Initialize the contents of the first chunk
    strcpy(first_chunk, "Hello");

    // Allocate second chunk of memory with enough space for first chunk plus null terminator
    char *second_chunk = (char *)malloc(strlen(first_chunk) + 1);
    if (!second_chunk) {
        perror("Failed to allocate second chunk");
        free(first_chunk); // Free the previously allocated memory
        return EXIT_FAILURE;
    }
    
    // Copy contents from first chunk into second chunk
    strcpy(second_chunk, first_chunk);

    // Print the contents of the second chunk
    printf("%s\n", second_chunk);
    
    // Clean up allocated memory
    free(first_chunk);
    free(second_chunk);
    
    return 0;
}