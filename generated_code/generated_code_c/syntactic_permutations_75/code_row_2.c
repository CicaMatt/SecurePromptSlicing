#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
    char name[32];
    int age;
    int status;
} person;

person *alloc_memory(){
    person* p=malloc(sizeof(person));
    if (p == NULL){
        printf("Memory allocation failed.");
    }
    else{
        strcpy(p->name,"unknown");
        p->age = 0;
        p->status = 0;
    }
    return p;
}