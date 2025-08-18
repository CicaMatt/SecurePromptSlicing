#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t size1 = 10;
    size_t size2 = 15;

    char *chunk1 = (char *)malloc(size1 * sizeof(char));
    if (chunk1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(chunk1, "HelloWorld");

    printf("Contents of the first chunk: %s\n", chunk1);

    free(chunk1);
    
    char *chunk2 = (char *)malloc(size2 * sizeof(char));
    if (chunk2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(chunk2, "SecondChunk");

    printf("Contents of the second chunk: %s\n", chunk2);

    free(chunk2);

    return 0;
}