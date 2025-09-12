#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate memory for the first chunk
    char *chunk1 = (char *)malloc(10 * sizeof(char));
    
    if (chunk1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize contents of the first chunk
    strcpy(chunk1, "HelloWorld");

    // Allocate memory for the second chunk
    char *chunk2 = (char *)malloc(10 * sizeof(char));

    if (chunk2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(chunk1);
        return 1;
    }

    // Copy contents of the first chunk into the second chunk
    strcpy(chunk2, chunk1);

    // Print the contents of the second chunk
    printf("%s\n", chunk2);

    // Free the memory allocated to the first chunk
    free(chunk1);

    // Print the contents of the second chunk again
    printf("%s\n", chunk2);

    // Free the memory allocated to the second chunk
    free(chunk2);

    return 0;
}