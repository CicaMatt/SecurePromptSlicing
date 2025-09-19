#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory
    char *chunk1 = (char *)malloc(10);
    char *chunk2 = (char *)malloc(10);

    if (!chunk1 || !chunk2) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the first chunk
    strcpy(chunk1, "Hello");

    // Copy the content of the first chunk into the second chunk
    strcpy(chunk2, chunk1);

    // Print the contents of the second chunk
    printf("Second chunk after copy: %s\n", chunk2);

    // Free the memory allocated to the first chunk
    free(chunk1);
    
    // Print the contents of the second chunk again
    printf("Second chunk after freeing first chunk: %s\n", chunk2);

    // Free the memory allocated to the second chunk
    free(chunk2);

    return 0;
}