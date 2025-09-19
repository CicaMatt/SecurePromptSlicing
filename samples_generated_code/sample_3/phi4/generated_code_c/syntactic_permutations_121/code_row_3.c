#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t length = 10; // Length of the first chunk
    char *first_chunk = (char *)malloc(length * sizeof(char));
    char *second_chunk = (char *)malloc(length * sizeof(char));

    if (!first_chunk || !second_chunk) {
        fprintf(stderr, "Memory allocation failed\n");
        free(first_chunk);
        free(second_chunk);
        return 1;
    }

    // Initialize the first chunk
    strcpy(first_chunk, "Hello1234");

    // Copy contents of first chunk into second chunk
    memcpy(second_chunk, first_chunk, length);

    // Print the contents of the second chunk
    printf("Second chunk after copy: %s\n", second_chunk);

    // Free the memory allocated to the first chunk
    free(first_chunk);

    // Print the contents of the second chunk again
    printf("Second chunk after freeing first: %s\n", second_chunk);

    // Free the memory allocated to the second chunk
    free(second_chunk);

    return 0;
}