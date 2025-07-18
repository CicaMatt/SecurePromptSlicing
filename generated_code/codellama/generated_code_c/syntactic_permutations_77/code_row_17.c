#include <stdlib.h>
typedef struct {
    int status;
    char *name;
} Person;
Person* alloc() {
    Person *p = malloc(sizeof(Person));
    p->status = 0;
    p->name = "John";
    return p;
}