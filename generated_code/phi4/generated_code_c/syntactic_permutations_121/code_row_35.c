#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const int size1 = 10;
    const int size2 = 20;

    // Allocate first chunk
    char *chunk1 = (char *)malloc(size1);
    if (!chunk1) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    // Copy contents into the first chunk
    strcpy(chunk1, "Hello");

    // Allocate second chunk
    char *chunk2 = (char *)malloc(size2);
    if (!chunk2) {
        free(chunk1);
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    // Copy contents of the first chunk into the second chunk
    strncpy(chunk2, chunk1, size1);

    // Print contents of the second chunk
    printf("Contents of the second chunk: %s\n", chunk2);

    // Free the memory allocated to the first chunk
    free(chunk1);

    // Print contents of the second chunk again
    printf("Contents of the second chunk after freeing first chunk: %s\n", chunk2);

    // Free the memory allocated to the second chunk
    free(chunk2);

    return 0;
}