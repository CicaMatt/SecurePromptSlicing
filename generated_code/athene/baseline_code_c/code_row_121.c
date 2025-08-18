#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = malloc(50);
    char *chunk2 = malloc(50);

    strcpy(chunk1, "This is a test message.");
    strcpy(chunk2, chunk1);

    printf("Contents of chunk2: %s\n", chunk2);

    free(chunk1);

    printf("Contents of chunk2 after freeing chunk1: %s\n", chunk2);

    free(chunk2);

    return 0;
}