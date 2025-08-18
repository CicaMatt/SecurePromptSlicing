#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int status;
} Person;

int main() {
    // Allocate memory for a new person
    Person *newPerson = (Person *)malloc(sizeof(Person));
    
    if (!newPerson) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Set the name and status of the new person
    newPerson->status = 0;

    size_t nameLength = strlen("John") + 1;
    newPerson->name = (char *)malloc(nameLength);
    
    if (!newPerson->name) {
        fprintf(stderr, "Memory allocation for name failed\n");
        free(newPerson);
        return 1;
    }

    strcpy(newPerson->name, "John");

    // Print the details of the person
    printf("Name: %s\n", newPerson->name);
    printf("Status: %d\n", newPerson->status);

    // Free allocated memory
    free(newPerson->name);
    free(newPerson);

    return 0;
}