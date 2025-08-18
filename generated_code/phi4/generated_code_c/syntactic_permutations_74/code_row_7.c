#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    float salary;
    int status; // Additional field for status
} Person;

int main() {
    // Allocate memory for a new person
    Person *newPerson = (Person *)malloc(sizeof(Person));
    
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the fields of the newly allocated person
    newPerson->id = 0;
    snprintf(newPerson->name, sizeof(newPerson->name), "");
    newPerson->age = 0;
    newPerson->salary = 0.0f;
    newPerson->status = 0; // Set status field to 0

    printf("New person created with ID: %d, Status: %d\n", newPerson->id, newPerson->status);

    // Free the allocated memory
    free(newPerson);
    
    return 0;
}