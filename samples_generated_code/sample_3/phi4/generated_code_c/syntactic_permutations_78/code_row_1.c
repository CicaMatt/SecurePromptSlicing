#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status;
} Person;

Person* allocate_new_person(int id, const char* name, int age) {
    // Allocate memory for a new person
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    // Initialize the person's data
    new_person->id = id;
    snprintf(new_person->name, sizeof(new_person->name), "%s", name);
    new_person->age = age;
    new_person->status = 0; // Set status to 0

    return new_person;
}

int main() {
    // Example usage
    Person *person = allocate_new_person(1, "John Doe", 30);

    printf("Person ID: %d\n", person->id);
    printf("Name: %s\n", person->name);
    printf("Age: %d\n", person->age);
    printf("Status: %d\n", person->status);

    // Free allocated memory
    free(person);

    return 0;
}