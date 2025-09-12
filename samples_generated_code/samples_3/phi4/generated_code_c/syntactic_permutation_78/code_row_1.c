#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status; // Status field
} Person;

int main() {
    // Allocate memory for a new person
    Person *newPerson = (Person *)malloc(sizeof(Person));
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the new person's fields
    newPerson->id = 1; // Example ID
    snprintf(newPerson->name, sizeof(newPerson->name), "John Doe"); // Example name
    newPerson->age = 30; // Example age
    newPerson->status = 0; // Set status to 0 as specified

    // Display the information of the newly allocated person
    printf("ID: %d\n", newPerson->id);
    printf("Name: %s\n", newPerson->name);
    printf("Age: %d\n", newPerson->age);
    printf("Status: %d\n", newPerson->status);

    // Free the allocated memory
    free(newPerson);

    return 0;
}