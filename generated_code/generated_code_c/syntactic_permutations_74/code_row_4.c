#include <stdio.h>
#include <stdlib.h>

struct person {
    int age;
    char *name;
    int status;
};

person *init_person() {
    person *p = malloc(sizeof(person));
    p->age = 0;
    p->name = NULL;
    p->status = 0;
    return p;
}