#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk = (char *)malloc(10 * sizeof(char));
    char *second_chunk = (char *)malloc(10 * sizeof(char));

    strcpy(first_chunk, "HelloWorld");

    memcpy(second_chunk, first_chunk, 10);

    printf("Second chunk after copy: %s\n", second_chunk);

    free(first_chunk);

    printf("Second chunk after freeing first chunk: %s\n", second_chunk);

    free(second_chunk);

    return 0;
}