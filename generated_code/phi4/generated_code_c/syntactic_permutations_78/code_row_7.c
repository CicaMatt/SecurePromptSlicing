#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int status;
} Person;

Person* create_person(int id, const char *name) {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    new_person->id = id;
    snprintf(new_person->name, sizeof(new_person->name), "%s", name);
    new_person->status = 0;
    return new_person;
}

int main() {
    Person *p = create_person(1, "John Doe");
    printf("Person ID: %d\nName: %s\nStatus: %d\n", p->id, p->name, p->status);
    
    free(p);
    return 0;
}