#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate two chunks of memory, each of size 10 bytes
    char *chunk1 = (char *)malloc(10);
    if (!chunk1) {
        perror("Failed to allocate chunk1");
        return 1;
    }

    char *chunk2 = (char *)malloc(10);
    if (!chunk2) {
        free(chunk1);
        perror("Failed to allocate chunk2");
        return 1;
    }
    
    // Initialize the first chunk with some data
    strcpy(chunk1, "abcdefghij");

    // Copy contents of the first chunk into the second chunk
    strcpy(chunk2, chunk1);

    printf("Contents of chunk2: %s\n", chunk2);
    
    // Free the first chunk
    free(chunk1);
    
    // Free the second chunk
    free(chunk2);
    
    return 0;
}