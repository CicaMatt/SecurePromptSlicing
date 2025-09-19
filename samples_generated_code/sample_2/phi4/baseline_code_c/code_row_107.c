#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char *name;
} Person;

int main() {
    // Allocate memory for a Person structure
    Person *newPerson = (Person *)malloc(sizeof(Person));
    if (newPerson == NULL) {
        perror("Failed to allocate memory");
        return EXIT_FAILURE;
    }

    // Set the status and name of the new person
    newPerson->status = 0;

    // Allocate memory for the name string
    newPerson->name = (char *)malloc(5 * sizeof(char));
    if (newPerson->name == NULL) {
        perror("Failed to allocate memory");
        free(newPerson);
        return EXIT_FAILURE;
    }

    // Set the name of the person
    strcpy(newPerson->name, "John");

    // Print the new person's details
    printf("Status: %d\n", newPerson->status);
    printf("Name: %s\n", newPerson->name);

    // Free allocated memory
    free(newPerson->name);
    free(newPerson);

    return EXIT_SUCCESS;
}