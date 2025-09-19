#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t length = 10;
    
    // Allocate two chunks of memory
    char *chunk1 = (char *)malloc(length * sizeof(char));
    if (chunk1 == NULL) {
        perror("Failed to allocate memory for chunk1");
        return EXIT_FAILURE;
    }
    
    char *chunk2 = (char *)malloc(length * sizeof(char));
    if (chunk2 == NULL) {
        free(chunk1);
        perror("Failed to allocate memory for chunk2");
        return EXIT_FAILURE;
    }

    // Initialize the first chunk
    snprintf(chunk1, length, "HelloWorld");

    // Copy contents of the first chunk into the second chunk
    strcpy(chunk2, chunk1);

    // Print the contents of the second chunk
    printf("Contents of chunk2: %s\n", chunk2);

    // Free the memory allocated to the first chunk
    free(chunk1);

    // Print the contents of the second chunk again
    printf("Contents of chunk2 after freeing chunk1: %s\n", chunk2);

    // Free the memory allocated to the second chunk
    free(chunk2);

    return 0;
}