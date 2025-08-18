#include <stdio.h>
#include <stdlib.h>

int main() {
    int *block;
    int size = sizeof(int);
    
    block = (int *)malloc(size);
    
    if (block == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    *block = 0;
    
    free(block);
    
    return 0;
}