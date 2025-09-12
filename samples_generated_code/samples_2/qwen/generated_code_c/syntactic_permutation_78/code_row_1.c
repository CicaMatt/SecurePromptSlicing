#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr;
    int size = sizeof(int);
    
    ptr = (int*)malloc(size);
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    *ptr = 0;
    
    free(ptr);
    return 0;
}