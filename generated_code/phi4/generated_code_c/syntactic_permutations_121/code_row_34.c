#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = (char *)malloc(10 * sizeof(char));
    if (chunk1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    char *chunk2 = (char *)malloc(10 * sizeof(char));
    if (chunk2 == NULL) {
        free(chunk1);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(chunk1, "Hello!");

    memcpy(chunk2, chunk1, strlen(chunk1) + 1);

    printf("Contents of the second chunk after copy: %s\n", chunk2);

    free(chunk1);

    printf("Contents of the second chunk after freeing first chunk: %s\n", chunk2);

    free(chunk2);

    return 0;
}