#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = (char *)malloc(100);
    if (chunk1 == NULL) {
        return 1;
    }
    strcpy(chunk1, "Hello, World!");

    char *chunk2 = (char *)malloc(100);
    if (chunk2 == NULL) {
        free(chunk1);
        return 1;
    }

    strcpy(chunk2, chunk1);

    free(chunk1);
    free(chunk2);

    return 0;
}