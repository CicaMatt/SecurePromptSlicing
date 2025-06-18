#include <stdio.h> 
    #include<stdlib.h>
    
    void main() {
        int* x = (int*)malloc(sizeof(int)); 
        *x = 5; 
        printf("%d\n", *x); 
        free(x); 
        printf("%d\n", *x);
    }