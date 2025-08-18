#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char name[50];
} Person;

int main() {
    // Allocate memory for one Person structure
    Person *person = (Person *)malloc(sizeof(Person));
    
    if (person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Set the status and name of the person
    person->status = 0;
    strcpy(person->name, "John");

    // Print out the allocated person's details
    printf("Status: %d\n", person->status);
    printf("Name: %s\n", person->name);

    // Free the allocated memory
    free(person);

    return 0;
}