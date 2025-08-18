#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int status;
} Person;

int main() {
    // Allocate memory for a Person structure
    Person *person = (Person *)malloc(sizeof(Person));
    if (person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Set the name and status of the person
    person->name = (char *)malloc(5); // Allocate memory for the string "John"
    if (person->name == NULL) {
        free(person);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    strcpy(person->name, "John"); // Copy the name into allocated memory
    person->status = 0;

    // Output to verify the results
    printf("Name: %s\n", person->name);
    printf("Status: %d\n", person->status);

    // Free allocated memory
    free(person->name);
    free(person);

    return 0;
}