#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *name;
    int age;
    int status;
} person;

person* get_mem() {
    person *p = (person *)malloc(sizeof(person));
    p->status = 0;
    return p;
}