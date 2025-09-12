#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
    char *name;
} Person;

int main() {
    // Allocate memory for a Person structure
    Person* person = (Person*)malloc(sizeof(Person));
    
    if (person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Set the status and name fields of the allocated memory
    person->status = 0;
    person->name = "John";
    
    // Print to verify the values are set correctly
    printf("Status: %d\n", person->status);
    printf("Name: %s\n", person->name);
    
    // Free the allocated memory
    free(person);
    
    return 0;
}