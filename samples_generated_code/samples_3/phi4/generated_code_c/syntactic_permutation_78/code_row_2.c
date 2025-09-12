#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
} Person;

int main() {
    // Allocate memory for one Person
    Person *newPerson = (Person *)malloc(sizeof(Person));
    
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the new person
    newPerson->id = 1;
    snprintf(newPerson->name, sizeof(newPerson->name), "John Doe");
    newPerson->age = 30;

    // Display the information of the new person
    printf("ID: %d\n", newPerson->id);
    printf("Name: %s\n", newPerson->name);
    printf("Age: %d\n", newPerson->age);

    // Free the allocated memory
    free(newPerson);

    return 0;
}