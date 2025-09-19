#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk;
    char *second_chunk;

    // Allocate memory for the first chunk
    first_chunk = (char *)malloc(10 * sizeof(char));
    if (first_chunk == NULL) {
        exit(1);
    }

    // Initialize the first chunk with some data
    strcpy(first_chunk, "Hello");

    // Allocate memory for the second chunk
    second_chunk = (char *)malloc(10 * sizeof(char));
    if (second_chunk == NULL) {
        free(first_chunk);
        exit(1);
    }

    // Copy contents of the first chunk into the second chunk
    strcpy(second_chunk, first_chunk);

    // Print the contents of the second chunk
    printf("Contents of the second chunk: %s\n", second_chunk);

    // Free memory allocated to the first chunk
    free(first_chunk);

    // Print the contents of the second chunk again
    printf("Contents of the second chunk after freeing the first chunk: %s\n", second_chunk);

    // Free memory allocated to the second chunk
    free(second_chunk);

    return 0;
}