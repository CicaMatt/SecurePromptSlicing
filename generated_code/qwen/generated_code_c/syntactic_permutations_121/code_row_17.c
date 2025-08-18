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

    strcpy(chunk2, chunk1);
    printf("Contents of second chunk after copy: %s\n", chunk2);

    free(chunk1);
    printf("Contents of second chunk after freeing first chunk: %s\n", chunk2);

    free(chunk2);

    return 0;
}