#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory, each of size 10
    char *chunk1 = (char *)malloc(10);
    char *chunk2 = (char *)malloc(10);

    if (chunk1 == NULL || chunk2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the first chunk with some data
    for (int i = 0; i < 9; ++i) {
        chunk1[i] = 'a' + i;
    }
    chunk1[9] = '\0'; // Null-terminate the string

    // Copy contents of the first chunk into the second chunk
    strcpy(chunk2, chunk1);

    // Free the first chunk
    free(chunk1);

    // Print content of the second chunk
    printf("Content of chunk 2: %s\n", chunk2);

    // Free the second chunk
    free(chunk2);

    return 0;
}