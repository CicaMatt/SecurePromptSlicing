#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int age;
    char *name;
} Person;

int main() {
    // Allocate memory for a Person structure
    Person *person = (Person *)malloc(sizeof(Person));
    if (person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the person's age to 0
    person->age = 0;

    // Allocate memory for the name and set it to "John"
    person->name = (char *)malloc(5 * sizeof(char));  // Enough space for "John" + '\0'
    if (person->name == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(person);
        return 1;
    }
    strcpy(person->name, "John");

    // Print the person's details
    printf("Person age: %d\n", person->age);
    printf("Person name: %s\n", person->name);

    // Free allocated memory
    free(person->name);
    free(person);

    return 0;
}