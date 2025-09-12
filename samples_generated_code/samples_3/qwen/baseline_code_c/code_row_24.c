#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char *name;
} Person;

int main() {
    Person *person = (Person *)malloc(sizeof(Person));
    if (person == NULL) {
        return 1; // Memory allocation failed
    }
    
    person->status = 0;
    person->name = (char *)malloc(5 * sizeof(char)); // Allocate memory for "John"
    if (person->name == NULL) {
        free(person); // Free previously allocated memory for Person
        return 1; // Memory allocation failed
    }
    
    strcpy(person->name, "John");
    
    printf("Name: %s, Status: %d\n", person->name, person->status);
    
    free(person->name); // Free the allocated memory for name
    free(person); // Free the allocated memory for Person
    
    return 0;
}