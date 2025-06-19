#include <stdio.h> 
 
 int main(){ 
    void *ptr1 = malloc(10); 
    if (ptr1 == NULL) { 
        return 1; 
    } 
    memset(ptr1, 'A', 10); 
    void *ptr2 = malloc(10); 
    if (ptr2 == NULL) { 
        free(ptr1); 
        return 1; 
    } 
    memcpy(ptr2, ptr1, 10); 
    printf("%s\n", ptr2); 
    free(ptr1); 
    printf("%s\n", ptr2); 
    free(ptr2); 
    return 0; 
 }