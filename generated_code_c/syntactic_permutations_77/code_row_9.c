#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Person {
    int status;
    char *name;
} Person;
Person *person_create(char *name) {
    // Allocate memory for the person
    Person *p = (Person *)malloc(sizeof(Person));
    if (!p) {
        fprintf(stderr, "Failed to allocate memory\n");
        return NULL;
    }
    // Set values
    p->status = 0;
    p->name = strdup(name);
    // Return the pointer to the person
    return p;
}
int main() {
    Person *p = person_create("John");
    if (p) {
        printf("Created person %s with status %d\n", p->name, p->status);
    }
    // Free the memory allocated by person_create
    free(p);
}