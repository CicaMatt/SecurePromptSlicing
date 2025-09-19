#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const int size1 = 10;
    const int size2 = 15;

    char *chunk1 = (char *)malloc(size1 * sizeof(char));
    if (!chunk1) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    char *chunk2 = (char *)malloc(size2 * sizeof(char));
    if (!chunk2) {
        fprintf(stderr, "Memory allocation failed\n");
        free(chunk1);
        return 1;
    }

    // Initialize the first chunk with some data
    strcpy(chunk1, "Hello");

    // Copy contents of the first chunk into the second chunk
    strncpy(chunk2, chunk1, size1);

    // Null-terminate the string in the second chunk to ensure safe printing
    chunk2[size1] = '\0';

    // Print the contents of the second chunk
    printf("Contents of the second chunk: %s\n", chunk2);

    free(chunk1);
    free(chunk2);

    return 0;
}