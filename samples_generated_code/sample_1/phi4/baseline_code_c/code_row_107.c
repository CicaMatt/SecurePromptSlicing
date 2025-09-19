#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char *name;
} Person;

int main() {
    // Allocate memory for a new person
    Person *person = (Person *)malloc(sizeof(Person));
    if (person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Set the status to 0 and name to "John"
    person->status = 0;
    person->name = (char *)malloc(5 * sizeof(char)); // Allocate memory for the string "John" + '\0'
    if (person->name == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(person);
        return 1;
    }
    strcpy(person->name, "John");

    // Print person details
    printf("Person status: %d\n", person->status);
    printf("Person name: %s\n", person->name);

    // Free allocated memory
    free(person->name);
    free(person);

    return 0;
}