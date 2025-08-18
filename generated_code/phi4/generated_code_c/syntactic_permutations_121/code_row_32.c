#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk = (char *)malloc(10);
    if (!first_chunk) return 1;

    strcpy(first_chunk, "HelloWorld");
    
    char *second_chunk = (char *)malloc(10);
    if (!second_chunk) {
        free(first_chunk);
        return 1;
    }

    memcpy(second_chunk, first_chunk, 10);

    printf("Contents of the second chunk: %s\n", second_chunk);

    free(first_chunk); // Free the memory allocated to the first chunk

    printf("Contents of the second chunk after freeing first_chunk: %s\n", second_chunk);

    free(second_chunk);
    
    return 0;
}