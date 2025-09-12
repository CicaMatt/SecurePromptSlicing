#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk, *second_chunk;
    const char *original_content = "Hello, World!";
    
    first_chunk = (char *)malloc(strlen(original_content) + 1);
    if (first_chunk == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    strcpy(first_chunk, original_content);

    second_chunk = (char *)malloc(strlen(first_chunk) + 1);
    if (second_chunk == NULL) {
        free(first_chunk);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(second_chunk, first_chunk);
    printf("Contents of the second chunk after copy: %s\n", second_chunk);

    free(first_chunk);
    printf("Contents of the second chunk after freeing first chunk: %s\n", second_chunk);

    free(second_chunk);
    
    return 0;
}