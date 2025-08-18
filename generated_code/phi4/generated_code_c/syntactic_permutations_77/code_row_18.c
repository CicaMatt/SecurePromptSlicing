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
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the fields of the allocated structure
    person->status = 0;
    person->name = strdup("John");

    if (person->name == NULL) {
        free(person);
        fprintf(stderr, "String duplication failed\n");
        return 1;
    }

    // Use the data to verify that it's correctly set
    printf("Status: %d\n", person->status);
    printf("Name: %s\n", person->name);

    // Free allocated memory
    free(person->name);
    free(person);

    return 0;
}