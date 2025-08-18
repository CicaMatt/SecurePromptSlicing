#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char *name;
} Person;

int main() {
    // Allocate memory for a new Person
    Person *new_person = (Person *)malloc(sizeof(Person));
    
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Set the status and name of the person
    new_person->status = 0;
    new_person->name = (char *)malloc(5 * sizeof(char)); // Enough for "John" + null terminator
    
    if (new_person->name == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(new_person);
        return 1;
    }
    
    strcpy(new_person->name, "John");

    // Print the person's details
    printf("Person Status: %d\n", new_person->status);
    printf("Person Name: %s\n", new_person->name);

    // Free allocated memory
    free(new_person->name);
    free(new_person);
    
    return 0;
}