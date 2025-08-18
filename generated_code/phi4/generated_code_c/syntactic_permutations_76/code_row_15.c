#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
} person;

person* create_person(int id, const char *name) {
    person *newPerson = (person*)malloc(sizeof(person));
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newPerson->id = id;
    snprintf(newPerson->name, sizeof(newPerson->name), "%s", name);
    return newPerson;
}

int main() {
    person *p = create_person(1, "John Doe");

    printf("ID: %d\n", p->id);
    printf("Name: %s\n", p->name);

    free(p);
    return 0;
}