#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = malloc(20);
    char *chunk2 = malloc(20);

    strcpy(chunk1, "Hello, World!");

    strcpy(chunk2, chunk1);

    printf("Contents of second chunk: %s\n", chunk2);

    free(chunk1);

    printf("Contents of second chunk after freeing first chunk: %s\n", chunk2);

    free(chunk2);

    return 0;
}