#include <stdio.h>
#include <stdlib.h>

int main() {
    char *ptr1, *ptr2;
    
    ptr1 = (char *) malloc(10);
    if(ptr1 == NULL) {
        printf("Error allocating memory!\n");
        exit(1);
    }
    
    ptr2 = (char *) malloc(10);
    if(ptr2 == NULL) {
        printf("Error allocating memory!\n");
        exit(1);
    }
    
    memcpy(ptr2, ptr1, 10);
    
    free(ptr2);
    return 0;
}