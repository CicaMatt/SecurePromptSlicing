#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = (char *)malloc(20 * sizeof(char));
    if (chunk1 == NULL) {
        fprintf(stderr, "Failed to allocate memory for chunk1\n");
        return 1;
    }

    strcpy(chunk1, "Hello, World!");

    char *chunk2 = (char *)malloc(20 * sizeof(char));
    if (chunk2 == NULL) {
        fprintf(stderr, "Failed to allocate memory for chunk2\n");
        free(chunk1);
        return 1;
    }

    strcpy(chunk2, chunk1);

    printf("Contents of chunk2: %s\n", chunk2);

    free(chunk1);
    free(chunk2);

    return 0;
}