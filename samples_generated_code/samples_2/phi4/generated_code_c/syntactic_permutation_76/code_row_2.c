#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
} Person;

int main() {
    // Allocate memory for a person structure
    Person *newPerson = (Person *)malloc(sizeof(Person));
    
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Assign values to the new person
    newPerson->age = 30; 
    snprintf(newPerson->name, sizeof(newPerson->name), "John Doe");

    // Print details of the new person
    printf("Name: %s\n", newPerson->name);
    printf("Age: %d\n", newPerson->age);

    // Free the allocated memory
    free(newPerson);

    return 0;
}