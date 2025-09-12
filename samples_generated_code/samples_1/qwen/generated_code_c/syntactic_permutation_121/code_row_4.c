#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk = (char *)malloc(10 * sizeof(char));
    char *second_chunk = (char *)malloc(10 * sizeof(char));

    if (first_chunk == NULL || second_chunk == NULL) {
        return 1;
    }

    strcpy(first_chunk, "HelloWorld");

    strcpy(second_chunk, first_chunk);

    printf("Contents of second chunk after copy: %s\n", second_chunk);

    free(first_chunk);

    printf("Contents of second chunk after freeing first chunk: %s\n", second_chunk);

    free(second_chunk);

    return 0;
}