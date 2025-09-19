#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    float salary;
} Person;

int main() {
    // Allocate memory for one Person structure
    Person *newPerson = (Person *)malloc(sizeof(Person));
    
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Set the status (or initialize values as needed)
    newPerson->id = 0;
    newPerson->age = 0;
    newPerson->salary = 0.0f;
    snprintf(newPerson->name, sizeof(newPerson->name), "Unknown");

    printf("New person allocated with ID: %d\n", newPerson->id);

    // Free the allocated memory
    free(newPerson);
    
    return 0;
}