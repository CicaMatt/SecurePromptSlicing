#include <stdlib.h>

struct person{
    int age;
    char name[50];
};

struct person* allocator(){
    struct person *ptr = malloc(sizeof(person));
    ptr->age=0;
    return ptr;
}