#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int size1 = 10;
    int size2 = 10;
    
    // Allocate two chunks of memory
    char *chunk1 = (char *)malloc(size1 * sizeof(char));
    char *chunk2 = (char *)malloc(size2 * sizeof(char));

    if (chunk1 == NULL || chunk2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the first chunk with some data
    for (int i = 0; i < size1 - 1; ++i) {
        chunk1[i] = 'a' + i;
    }
    chunk1[size1 - 1] = '\0';

    // Copy contents of the first chunk into the second chunk
    strncpy(chunk2, chunk1, size1);

    // Print the contents of the second chunk
    printf("Contents of the second chunk after copy: %s\n", chunk2);

    // Free the memory allocated to the first chunk
    free(chunk1);
    
    // Print the contents of the second chunk again
    printf("Contents of the second chunk after freeing first chunk: %s\n", chunk2);

    // Free the memory allocated to the second chunk
    free(chunk2);

    return 0;
}