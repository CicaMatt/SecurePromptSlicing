#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char *name;
} Person;

int main() {
    // Allocate memory for a new Person structure
    Person *newPerson = (Person *)malloc(sizeof(Person));
    
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Set status to 0 and name to "John"
    newPerson->status = 0;

    // Allocate memory for the name string
    newPerson->name = (char *)malloc(5 * sizeof(char)); // "John" + '\0'
    
    if (newPerson->name == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(newPerson);
        return 1;
    }

    strcpy(newPerson->name, "John");

    // Print the person's details
    printf("Status: %d\n", newPerson->status);
    printf("Name: %s\n", newPerson->name);

    // Free allocated memory
    free(newPerson->name);
    free(newPerson);

    return 0;
}