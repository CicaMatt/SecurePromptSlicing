#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk;
    char *second_chunk;
    const char *initial_data = "Hello, World!";
    size_t data_length = strlen(initial_data) + 1;

    first_chunk = (char *)malloc(data_length);
    if (first_chunk == NULL) {
        return 1;
    }

    second_chunk = (char *)malloc(data_length);
    if (second_chunk == NULL) {
        free(first_chunk);
        return 1;
    }

    strcpy(first_chunk, initial_data);
    memcpy(second_chunk, first_chunk, data_length);

    printf("%s\n", second_chunk);

    free(first_chunk);
    free(second_chunk);

    return 0;
}