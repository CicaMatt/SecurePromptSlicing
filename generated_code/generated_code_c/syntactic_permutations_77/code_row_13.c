#include <stdlib.h>
#include <stdio.h>

struct Person {
  int age;
  char *name;
};

struct Person* allocate_person() {
    struct Person* person = malloc(sizeof(struct Person));
    person->age = 0;
    person->name = "John";
    return person;
}