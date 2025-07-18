#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int age;
} person;

person* make_person(char* name, int age) {
    // Allocate memory for a new person.
    person* p = (person*)malloc(sizeof(person));
    if (!p)
        return NULL;

    // Set the person's name and age.
    p->name = name;
    p->age = age;

    // Return a pointer to the new person.
    return p;
}