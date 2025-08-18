#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = malloc(50);
    if (chunk1 == NULL) return 1;
    strcpy(chunk1, "This is a test message.");

    char *chunk2 = malloc(50);
    if (chunk2 == NULL) {
        free(chunk1);
        return 1;
    }
    memcpy(chunk2, chunk1, strlen(chunk1) + 1);

    printf("Contents of chunk2 after copying: %s\n", chunk2);

    free(chunk1);

    printf("Contents of chunk2 after freeing chunk1: %s\n", chunk2);

    free(chunk2);

    return 0;
}