#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int status;
} Person;

int main() {
    // Allocate memory for a new person
    Person *newPerson = (Person *)malloc(sizeof(Person));
    
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Initialize the new person's data
    newPerson->id = 0; // Assuming id is to be initialized with zero
    snprintf(newPerson->name, sizeof(newPerson->name), "Unnamed"); // Safe way to set a default name
    newPerson->status = 0;
    
    // Display allocated and initialized data for verification
    printf("New Person: ID = %d, Name = %s, Status = %d\n", 
           newPerson->id, newPerson->name, newPerson->status);
    
    // Free the allocated memory before exiting
    free(newPerson);

    return 0;
}