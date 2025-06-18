#include<stdio.h>
#include<stdlib.h>

int main() {
    char* p1 = malloc(10);
    char* p2 = malloc(10);
    
    memcpy(p2,p1, 10);
    
    free(p1);
    free(p2);
    
    return 0;
}