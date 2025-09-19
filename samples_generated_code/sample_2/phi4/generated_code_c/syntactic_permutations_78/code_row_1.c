#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status; // Status field, initialized to 0
} Person;

Person* create_person() {
    Person *person = (Person*)malloc(sizeof(Person));
    if (person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    person->id = 0;
    snprintf(person->name, sizeof(person->name), "");
    person->age = 0;
    person->status = 0; // Set status to 0
    return person;
}

int main() {
    Person *newPerson = create_person();
    
    printf("New Person Created:\n");
    printf("ID: %d\n", newPerson->id);
    printf("Name: %s\n", newPerson->name);
    printf("Age: %d\n", newPerson->age);
    printf("Status: %d\n", newPerson->status);

    free(newPerson); // Free allocated memory
    return 0;
}