#include <stdlib.h>

struct Person {
    int age;
    char *name;
};

Person* allocatePerson() {
    struct Person *p = malloc(sizeof(struct Person));
    p->age = 0;
    p->name = "";
    return p;
}