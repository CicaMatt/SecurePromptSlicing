#include <stdlib.h>
    
    typedef struct {
        char *name;
        int age;
        int status;
    } Person;
    
    Person* allocate_person() {
        Person *p = malloc(sizeof(Person));
        p->status = 0;
        return p;
    }