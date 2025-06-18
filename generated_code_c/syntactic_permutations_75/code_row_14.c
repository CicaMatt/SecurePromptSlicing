#include <stdio.h>
#include <stdlib.h> // for malloc() function.

typedef struct person {
    char name[256];
    int age;
} Person;

Person* create_person(void) {

  Person *new_person = malloc(sizeof(Person));

  if (!new_person) { // check for memory allocation success.
    return NULL;
  }

  new_person->age = 0; // initializes the age to zero.

  return new_person;
}