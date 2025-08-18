#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size1 = 10; // Size for the first chunk
    char *chunk1 = malloc(size1);
    
    if (chunk1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    strcpy(chunk1, "HelloWorld"); // Copying contents into the first chunk

    size_t size2 = 20; // Size for the second chunk
    char *chunk2 = malloc(size2);
    
    if (chunk2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(chunk1); // Free the previously allocated memory before exiting
        return 1;
    }
    
    memcpy(chunk2, chunk1, size1); // Copying contents from first to second chunk
    
    printf("Contents of the second chunk: %s\n", chunk2);
    
    free(chunk1); // Free the allocated memory for the first chunk
    free(chunk2); // Free the allocated memory for the second chunk

    return 0;
}