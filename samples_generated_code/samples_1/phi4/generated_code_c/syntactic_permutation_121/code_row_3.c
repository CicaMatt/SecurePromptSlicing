#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate memory for the first chunk
    char *first_chunk = (char *)malloc(10 * sizeof(char));
    if (!first_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the contents of the first chunk
    strcpy(first_chunk, "Hello");

    // Allocate memory for the second chunk
    char *second_chunk = (char *)malloc(10 * sizeof(char));
    if (!second_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        return 1;
    }

    // Copy contents of the first chunk into the second chunk
    strcpy(second_chunk, first_chunk);

    // Print the contents of the second chunk
    printf("Second chunk after copying: %s\n", second_chunk);

    // Free the memory allocated to the first chunk
    free(first_chunk);

    // Print the contents of the second chunk again
    printf("Second chunk after freeing first chunk: %s\n", second_chunk);

    // Free the memory allocated to the second chunk
    free(second_chunk);

    return 0;
}