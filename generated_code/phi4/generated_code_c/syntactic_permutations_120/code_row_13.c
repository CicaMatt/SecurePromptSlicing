#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 10; // Define the size of the memory chunks

    // Allocate two chunks of memory
    char *chunk1 = (char *)malloc(size);
    if (chunk1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    char *chunk2 = (char *)malloc(size);
    if (chunk2 == NULL) {
        free(chunk1); // Free the first chunk before exiting
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize and copy data into the first chunk
    for (size_t i = 0; i < size; ++i) {
        chunk1[i] = 'A' + i % 26;
    }

    // Copy contents of the first chunk to the second chunk
    memcpy(chunk2, chunk1, size);

    // Print the content of the second chunk
    printf("Content of the second chunk: ");
    for (size_t i = 0; i < size; ++i) {
        putchar(chunk2[i]);
    }
    printf("\n");

    // Free allocated memory
    free(chunk1);
    free(chunk2);

    return 0;
}