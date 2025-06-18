#include<stdio.h>
#include <stdlib.h>

struct person{
    char *name;
};

int main(){
    
    struct person* p = malloc(sizeof(struct person)); 
    p->name="John"; // set the name to John
}