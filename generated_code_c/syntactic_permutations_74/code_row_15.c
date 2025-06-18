#include <stdio.h> 
#include <stdlib.h>  
struct person {  
    char *name; 
    int age;  
};  
int main() {  
    struct person *ptr;  
    ptr = (struct person*) malloc(sizeof(struct person)); 
    return 0;  
}