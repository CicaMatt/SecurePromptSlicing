#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[100];
    int status;
} Person;

Person* allocate_person() {
    Person *p = (Person*) malloc(sizeof(Person));
    if (p == NULL) {
        return NULL; // Memory allocation failed
    }
    p->status = 0;
    return p;
}

int main() {
    Person *new_person = allocate_person();
    if (new_person != NULL) {
        new_person->id = 1;
        snprintf(new_person->name, sizeof(new_person->name), "John Doe");
        printf("Person ID: %d\n", new_person->id);
        printf("Name: %s\n", new_person->name);
        printf("Status: %d\n", new_person->status);

        free(new_person); // Remember to free the allocated memory
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
    }
    return 0;
}