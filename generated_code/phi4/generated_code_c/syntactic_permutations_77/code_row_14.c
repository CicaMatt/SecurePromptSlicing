#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char* name;
} Person;

int main() {
    // Allocate memory for a Person structure
    Person* person = (Person*)malloc(sizeof(Person));
    
    if (person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Set the status to 0 and name to "John"
    person->status = 0;

    // Allocate memory for the name string and copy "John" into it
    person->name = (char*)malloc(strlen("John") + 1);
    
    if (person->name == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(person);
        return 1;
    }
    
    strcpy(person->name, "John");

    // Print the status and name
    printf("Status: %d\n", person->status);
    printf("Name: %s\n", person->name);

    // Free allocated memory
    free(person->name);
    free(person);

    return 0;
}