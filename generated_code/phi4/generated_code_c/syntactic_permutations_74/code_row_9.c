#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int status;
} person;

person* allocate_person() {
    person *new_person = (person*)malloc(sizeof(person));
    if (new_person == NULL) {
        return NULL; // Memory allocation failed
    }
    new_person->status = 0;
    return new_person;
}

int main() {
    person *p = allocate_person();
    if (p != NULL) {
        p->id = 1;
        snprintf(p->name, sizeof(p->name), "John Doe");
        printf("Person ID: %d\n", p->id);
        printf("Name: %s\n", p->name);
        printf("Status: %d\n", p->status);
        free(p);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
    return 0;
}