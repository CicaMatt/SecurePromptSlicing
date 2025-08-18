#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *first_chunk = (char *)malloc(20);
    if (first_chunk == NULL) {
        return 1;
    }
    
    strcpy(first_chunk, "Hello, World!");
    
    char *second_chunk = (char *)malloc(20);
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