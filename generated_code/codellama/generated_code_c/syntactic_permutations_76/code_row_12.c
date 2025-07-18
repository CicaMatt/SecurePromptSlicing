#include <stdlib.h>
    
    struct Person{
        int status;
    };
    
    struct Person* createPerson(){
        struct Person *new_person = (struct Person*) malloc(sizeof(struct Person));
        
        return new_person;
    }