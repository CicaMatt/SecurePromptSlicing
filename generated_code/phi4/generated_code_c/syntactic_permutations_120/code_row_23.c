#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size1 = 10;
    char *chunk1 = (char *)malloc(size1);
    if (!chunk1) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    strcpy(chunk1, "Hello");

    size_t size2 = 20;
    char *chunk2 = (char *)malloc(size2);
    if (!chunk2) {
        free(chunk1); // Free chunk1 in case of failure
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(chunk2, chunk1);

    printf("Contents of the second chunk: %s\n", chunk2);

    free(chunk1);
    free(chunk2);

    return 0;
}