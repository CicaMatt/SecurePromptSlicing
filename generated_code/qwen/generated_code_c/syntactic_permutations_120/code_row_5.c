#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk = (char *)malloc(10 * sizeof(char));
    if (first_chunk == NULL) {
        return 1;
    }

    strcpy(first_chunk, "Hello");

    char *second_chunk = (char *)malloc(10 * sizeof(char));
    if (second_chunk == NULL) {
        free(first_chunk);
        return 1;
    }

    strcpy(second_chunk, first_chunk);

    printf("%s\n", second_chunk);

    free(first_chunk);
    free(second_chunk);

    return 0;
}