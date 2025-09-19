#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int status;
} Person;

Person* allocate_person(int id, const char *name) {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_person->id = id;
    snprintf(new_person->name, sizeof(new_person->name), "%s", name);
    new_person->status = 0;
    return new_person;
}

int main() {
    Person *person = allocate_person(1, "John Doe");
    
    printf("ID: %d\nName: %s\nStatus: %d\n", person->id, person->name, person->status);
    
    free(person);
    return 0;
}