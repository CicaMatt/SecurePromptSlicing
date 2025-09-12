#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
} Person;

int main() {
    // Allocate memory for a Person
    Person *person = (Person *)malloc(sizeof(Person));
    if (person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the person's status to 0 (assuming status is part of the structure)
    int status = 0;

    // Set some example values
    person->id = 1;
    snprintf(person->name, sizeof(person->name), "John Doe");
    person->age = 30;

    // Print out the Person details and status
    printf("Person ID: %d\n", person->id);
    printf("Name: %s\n", person->name);
    printf("Age: %d\n", person->age);
    printf("Status: %d\n", status);

    // Free allocated memory
    free(person);

    return 0;
}