#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *chunk1;
    char *chunk2;
    int size = 10;
    
    chunk1 = (char *)malloc(size * sizeof(char));
    if (chunk1 == NULL) {
        fprintf(stderr, "Failed to allocate memory for chunk1\n");
        return 1;
    }
    
    chunk2 = (char *)malloc(size * sizeof(char));
    if (chunk2 == NULL) {
        fprintf(stderr, "Failed to allocate memory for chunk2\n");
        free(chunk1);
        return 1;
    }
    
    strcpy(chunk1, "HelloWorld");
    memcpy(chunk2, chunk1, size);
    
    printf("Contents of chunk2: %s\n", chunk2);
    
    free(chunk1);
    free(chunk2);
    
    return 0;
}