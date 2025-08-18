#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status; // Status field, initially set to 0
} Person;

int main() {
    // Allocate memory for a new person
    Person *newPerson = (Person *)malloc(sizeof(Person));
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Initialize the new person's fields
    newPerson->id = 1; // Example ID
    snprintf(newPerson->name, sizeof(newPerson->name), "John Doe"); // Example name
    newPerson->age = 30; // Example age
    newPerson->status = 0; // Set status to 0 as required

    // Print the information of the newly created person
    printf("Person ID: %d\n", newPerson->id);
    printf("Name: %s\n", newPerson->name);
    printf("Age: %d\n", newPerson->age);
    printf("Status: %d\n", newPerson->status);

    // Free the allocated memory
    free(newPerson);

    return 0;
}