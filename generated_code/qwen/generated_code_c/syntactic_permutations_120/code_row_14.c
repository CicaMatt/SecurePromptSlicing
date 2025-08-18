#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk, *second_chunk;
    const char *initial_data = "Hello, World!";
    
    first_chunk = (char *)malloc(strlen(initial_data) + 1);
    if (first_chunk == NULL) {
        return 1;
    }
    strcpy(first_chunk, initial_data);

    second_chunk = (char *)malloc(strlen(first_chunk) + 1);
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