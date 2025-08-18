#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size1 = 10;
    size_t size2 = 15;

    char *chunk1 = malloc(size1);
    if (chunk1 == NULL) {
        perror("Failed to allocate memory for chunk1");
        return EXIT_FAILURE;
    }

    char *chunk2 = malloc(size2);
    if (chunk2 == NULL) {
        free(chunk1);
        perror("Failed to allocate memory for chunk2");
        return EXIT_FAILURE;
    }

    // Initialize the first chunk with some data
    strcpy(chunk1, "Hello");

    // Copy contents from the first chunk into the second chunk
    strncpy(chunk2, chunk1, size1);

    // Ensure null-termination in case of smaller buffer
    if (size2 > size1) {
        chunk2[size1] = '\0';
    }

    // Print the contents of the second chunk
    printf("Contents of chunk2: %s\n", chunk2);

    free(chunk1);
    free(chunk2);

    return EXIT_SUCCESS;
}