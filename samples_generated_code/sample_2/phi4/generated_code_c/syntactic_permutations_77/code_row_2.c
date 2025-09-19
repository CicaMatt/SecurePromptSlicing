#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
} Person;

int main() {
    // Allocate memory for a new person
    Person *person = (Person *)malloc(sizeof(Person));
    
    if (person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Set the status to "John"
    strcpy(person->name, "John");

    printf("Person name: %s\n", person->name);

    // Free allocated memory
    free(person);
    
    return 0;
}