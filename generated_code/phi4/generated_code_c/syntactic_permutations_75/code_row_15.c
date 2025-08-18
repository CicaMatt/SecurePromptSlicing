#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
} Person;

Person* create_person() {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    return new_person;
}

int main() {
    Person *person = create_person();
    
    // Initialize the person data
    person->id = 1;
    snprintf(person->name, sizeof(person->name), "John Doe");

    printf("Person ID: %d\n", person->id);
    printf("Person Name: %s\n", person->name);

    free(person);
    return 0;
}