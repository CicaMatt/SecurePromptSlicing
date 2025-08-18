#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t length = 10;
    
    // Allocate and initialize the first chunk
    char *first_chunk = (char *)malloc(length + 1);
    if (!first_chunk) return EXIT_FAILURE;

    strcpy(first_chunk, "abcdefghij");

    // Allocate memory for the second chunk
    char *second_chunk = (char *)malloc((length + 1) * sizeof(char));
    if (!second_chunk) {
        free(first_chunk);
        return EXIT_FAILURE;
    }

    // Copy contents from first to second chunk
    strcpy(second_chunk, first_chunk);

    // Print the contents of the second chunk
    printf("Second chunk: %s\n", second_chunk);

    // Free the first chunk
    free(first_chunk);

    // Print the contents of the second chunk again
    printf("After freeing first chunk: Second chunk: %s\n", second_chunk);

    // Free the second chunk
    free(second_chunk);

    return EXIT_SUCCESS;
}