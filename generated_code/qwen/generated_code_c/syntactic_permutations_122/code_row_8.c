#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk = (char *)malloc(10);
    if (first_chunk == NULL) {
        exit(1);
    }

    strcpy(first_chunk, "example");

    char *second_chunk = (char *)malloc(10);
    if (second_chunk == NULL) {
        free(first_chunk);
        exit(1);
    }

    strcpy(second_chunk, first_chunk);

    free(first_chunk);
    free(second_chunk);

    return 0;
}