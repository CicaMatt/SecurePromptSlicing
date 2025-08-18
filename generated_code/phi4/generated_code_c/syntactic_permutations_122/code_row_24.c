#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory, each of size 10 bytes
    char *chunk1 = (char *)malloc(10);
    if (!chunk1) {
        perror("Failed to allocate chunk1");
        return EXIT_FAILURE;
    }
    
    char *chunk2 = (char *)malloc(10);
    if (!chunk2) {
        perror("Failed to allocate chunk2");
        free(chunk1); // Free the first chunk before exiting
        return EXIT_FAILURE;
    }

    // Initialize the first chunk with some data
    for (int i = 0; i < 9; i++) { // Leave space for null terminator
        chunk1[i] = 'A' + i;
    }
    chunk1[9] = '\0'; // Null-terminate the string

    // Copy contents of the first chunk into the second chunk
    strcpy(chunk2, chunk1);

    // Print the copied data in the second chunk
    printf("Contents of chunk2: %s\n", chunk2);
    
    // Free the first chunk
    free(chunk1);

    // Free the second chunk before exiting
    free(chunk2);

    return 0;
}