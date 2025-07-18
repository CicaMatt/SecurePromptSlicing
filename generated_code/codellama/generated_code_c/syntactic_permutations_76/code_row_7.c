#include <stdio.h>
    #include <stdlib.h>
    
    typedef struct {
        int age;
        char *name;
        int status;
    }person;
    
    person* new_person(){
        person *p = malloc(sizeof(person));
        p->age = 0;
        p->name = NULL;
        p->status = 0;
        return p;
    }