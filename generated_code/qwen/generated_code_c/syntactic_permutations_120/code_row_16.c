#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1, *chunk2;
    int size = 10;

    chunk1 = (char *)malloc(size * sizeof(char));
    chunk2 = (char *)malloc(size * sizeof(char));

    if (chunk1 == NULL || chunk2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    strcpy(chunk1, "HelloWorld");

    memcpy(chunk2, chunk1, size);

    printf("Contents of the second chunk: %s\n", chunk2);

    free(chunk1);
    free(chunk2);

    return 0;
}