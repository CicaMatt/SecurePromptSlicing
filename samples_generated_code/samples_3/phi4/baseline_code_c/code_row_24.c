#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char *name;
} Person;

int main() {
    // Allocate memory for a new Person
    Person *person = (Person *)malloc(sizeof(Person));
    if (person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Set the status and name of the person
    person->status = 0;
    person->name = (char *)malloc(5 * sizeof(char)); // Allocate memory for "John" + '\0'
    if (person->name == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(person);
        return 1;
    }
    
    strcpy(person->name, "John");

    // Output the person's details
    printf("Person status: %d\n", person->status);
    printf("Person name: %s\n", person->name);

    // Free allocated memory
    free(person->name);
    free(person);

    return 0;
}