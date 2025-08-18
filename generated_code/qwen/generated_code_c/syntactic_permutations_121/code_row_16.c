#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = (char *)malloc(20 * sizeof(char));
    char *chunk2 = (char *)malloc(20 * sizeof(char));

    if (chunk1 == NULL || chunk2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(chunk1, "Hello, World!");
    memcpy(chunk2, chunk1, strlen(chunk1) + 1);

    printf("Contents of chunk1: %s\n", chunk1);
    free(chunk1);

    printf("Contents of chunk2: %s\n", chunk2);
    free(chunk2);

    return 0;
}