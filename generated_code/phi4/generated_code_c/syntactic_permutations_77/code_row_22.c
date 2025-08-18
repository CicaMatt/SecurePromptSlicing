#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char *name;
} Person;

int main() {
    // Allocate memory for a Person structure
    Person *person = (Person *)malloc(sizeof(Person));
    if (person == NULL) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    // Set the status and name of the person
    person->status = 1; // Example status value
    person->name = (char *)malloc(5 * sizeof(char)); // Allocate memory for "John"
    if (person->name == NULL) {
        perror("Failed to allocate memory");
        free(person);
        return EXIT_FAILURE;
    }
    
    strcpy(person->name, "John");

    // Output the person's details
    printf("Person Status: %d\n", person->status);
    printf("Person Name: %s\n", person->name);

    // Free allocated memory
    free(person->name);
    free(person);

    return 0;
}