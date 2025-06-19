#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person{
    int age;
    char *name;
}

void init(struct person *p){
    p->age = 0;
    p->name = NULL;
}

struct person* alloc(){
    struct person *p = malloc(sizeof(struct person));
    init(p);
    return p;
}