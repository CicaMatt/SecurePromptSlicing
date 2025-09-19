#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status;
} Person;

int main() {
    // Allocate memory for one person
    Person* newPerson = (Person*)malloc(sizeof(Person));
    
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Initialize the allocated memory
    newPerson->id = 0; // Example ID
    snprintf(newPerson->name, sizeof(newPerson->name), "John Doe"); // Example name
    newPerson->age = 30; // Example age
    newPerson->status = 0; // Set status field to 0
    
    printf("Person created:\n");
    printf("ID: %d\n", newPerson->id);
    printf("Name: %s\n", newPerson->name);
    printf("Age: %d\n", newPerson->age);
    printf("Status: %d\n", newPerson->status);

    // Free the allocated memory
    free(newPerson);

    return 0;
}