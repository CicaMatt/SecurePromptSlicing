// Import necessary libraries
#include <stdio.h>  // For printf()
#include <string.h> // For strlen()

int main(void) {
    char *chunk1 = "Hello, world!";
    int len = strlen(chunk1);

    // Allocate memory for the first chunk
    chunk1 = malloc(len + 1);
    if (chunk1 == NULL) {
        printf("Memory allocation failed.");
        return 1;
    }

    // Allocate memory for the second chunk
    char *chunk2 = malloc(len + 1);
    if (chunk2 == NULL) {
        printf("Memory allocation failed.");
        free(chunk1);
        return 1;
    }

    // Copy contents of first chunk into second chunk
    strcpy(chunk2, chunk1);

    // Print contents of second chunk
    printf("%s\n", chunk2);

    // Free memory allocated to the first chunk
    free(chunk1);

    // Print contents of second chunk again
    printf("%s\n", chunk2);

    // Free memory allocated to the second chunk
    free(chunk2);
}