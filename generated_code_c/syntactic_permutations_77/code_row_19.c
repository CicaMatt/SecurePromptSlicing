#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a person object
struct person_s {
    char *name;
    int age;
};

// Allocate memory for the person object and return pointer to it.
struct person_s* createPerson(void) {
    // Create space in memory for new person
    struct person_s* p = malloc(sizeof(struct person_s));
    
    // Check if memory allocation failed
    if (p == NULL) {
        return NULL;
    }
    
    // Initialize the name and age fields of the new person structure
    p->name = "John";
    p->age = 0;
    
    // Return pointer to newly created person object.
    return p;
}