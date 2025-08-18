#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1 = malloc(20 * sizeof(char));
    char *chunk2 = malloc(20 * sizeof(char));
    
    strcpy(chunk1, "Hello, World!");
    strcpy(chunk2, chunk1);
    
    printf("%s\n", chunk2);
    
    free(chunk1);
    free(chunk2);
    
    return 0;
}