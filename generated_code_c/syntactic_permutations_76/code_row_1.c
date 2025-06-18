#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* name;
    int age;
    int height;
    int weight;
    int status;
} person;

person* alloc() {    
    return (person*)malloc(sizeof(person));
}