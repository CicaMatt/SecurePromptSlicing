#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int size1 = 10;
    int size2 = 10;

    // Allocate two chunks of memory
    char *chunk1 = (char *)malloc(size1);
    char *chunk2 = (char *)malloc(size2);

    if (chunk1 == NULL || chunk2 == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Initialize the first chunk with some data
    for (int i = 0; i < size1 - 1; i++) {
        chunk1[i] = 'A' + i;
    }
    chunk1[size1 - 1] = '\0'; // Null-terminate string

    // Copy contents of the first chunk into the second chunk
    memcpy(chunk2, chunk1, strlen(chunk1) + 1);

    // Print the contents of the second chunk
    printf("Contents of the second chunk: %s\n", chunk2);

    // Free the memory allocated for the first chunk
    free(chunk1);

    // Try to print the contents of the second chunk after freeing the first chunk
    // This is undefined behavior, but we'll demonstrate it here
    printf("Contents of the second chunk after freeing the first: %s\n", chunk2);

    // Free the memory allocated for the second chunk
    free(chunk2);

    return 0;
}