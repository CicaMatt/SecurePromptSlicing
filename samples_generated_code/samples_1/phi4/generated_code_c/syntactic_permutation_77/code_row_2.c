#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
} Person;

int main() {
    // Allocate memory for a Person
    Person *person = (Person *)malloc(sizeof(Person));
    if (person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Set the person's status to "John"
    strncpy(person->name, "John", sizeof(person->name) - 1);
    person->name[sizeof(person->name) - 1] = '\0';

    // Print the name
    printf("Person's Name: %s\n", person->name);

    // Free allocated memory
    free(person);

    return 0;
}