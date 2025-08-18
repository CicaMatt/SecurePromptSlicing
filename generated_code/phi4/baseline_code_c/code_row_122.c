#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk = (char *)malloc(10);
    if (!first_chunk) {
        return 1;
    }
    
    char *second_chunk = (char *)malloc(10);
    if (!second_chunk) {
        free(first_chunk);
        return 1;
    }

    // Initialize first chunk with some data
    for (int i = 0; i < 10; ++i) {
        first_chunk[i] = 'A' + i;
    }
    
    // Copy contents of the first chunk into the second chunk
    memcpy(second_chunk, first_chunk, 10);
    
    // Free the first chunk
    free(first_chunk);

    // Display content of the second chunk
    for (int i = 0; i < 10; ++i) {
        printf("%c ", second_chunk[i]);
    }
    printf("\n");

    // Free the second chunk
    free(second_chunk);
    
    return 0;
}