#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t length = 10;
    
    // Allocate two chunks of memory
    char *firstChunk = (char *)malloc(length + 1);
    char *secondChunk = (char *)malloc(length + 1);

    if (firstChunk == NULL || secondChunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the first chunk
    snprintf(firstChunk, length + 1, "%s", "HelloWorld");

    // Copy contents of the first chunk into the second chunk
    strcpy(secondChunk, firstChunk);

    // Print the contents of the second chunk
    printf("Contents of second chunk: %s\n", secondChunk);

    // Free the memory allocated to the first chunk
    free(firstChunk);

    // Print the contents of the second chunk again
    printf("Contents of second chunk after freeing first chunk: %s\n", secondChunk);

    // Free the memory allocated to the second chunk
    free(secondChunk);

    return 0;
}