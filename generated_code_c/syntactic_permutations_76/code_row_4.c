#include <stdlib.h>

struct Person {
    int age;
    char* name;
    int status;
};

struct Person* allocate_person() {
    struct Person* person = (struct Person*) malloc(sizeof(struct Person));
    return person;
}