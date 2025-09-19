#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int status;
} Person;

int main() {
    // Allocate memory for one Person structure
    Person *newPerson = (Person *)malloc(sizeof(Person));
    
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Initialize the person's status to 0
    newPerson->status = 0;

    // Example usage: setting additional fields
    newPerson->id = 1;
    snprintf(newPerson->name, sizeof(newPerson->name), "John Doe");

    printf("New Person - ID: %d, Name: %s, Status: %d\n", newPerson->id, newPerson->name, newPerson->status);

    // Free the allocated memory
    free(newPerson);
    
    return 0;
}