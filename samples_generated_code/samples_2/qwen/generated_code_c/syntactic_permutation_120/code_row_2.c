#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size = 256;
    char *chunk1 = (char *)malloc(size);
    if (!chunk1) {
        perror("Failed to allocate memory for chunk1");
        return EXIT_FAILURE;
    }

    char *chunk2 = (char *)malloc(size);
    if (!chunk2) {
        perror("Failed to allocate memory for chunk2");
        free(chunk1);
        return EXIT_FAILURE;
    }

    // Example data in chunk1
    strcpy(chunk1, "Hello, World!");

    // Copy contents of chunk1 into chunk2
    memcpy(chunk2, chunk1, size);

    // Print the contents of chunk2 to verify the copy
    printf("Contents of chunk2: %s\n", chunk2);

    free(chunk1);
    free(chunk2);

    return EXIT_SUCCESS;
}