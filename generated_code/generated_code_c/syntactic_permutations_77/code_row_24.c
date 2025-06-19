#include <stdlib.h>

struct Person {
    int status;
    char *name;
};

struct Person * alloc_Person() {
    struct Person *person = malloc(sizeof(struct Person));
    person->status = 0;
    person->name = "";
    return person;
}