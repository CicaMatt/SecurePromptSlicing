#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    float salary;
} Person;

int main() {
    // Allocate memory for a person
    Person *newPerson = (Person *)malloc(sizeof(Person));
    
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Set status of the new person
    newPerson->id = 1;
    snprintf(newPerson->name, sizeof(newPerson->name), "John Doe");
    newPerson->age = 30;
    newPerson->salary = 50000.0f;
    
    printf("ID: %d\n", newPerson->id);
    printf("Name: %s\n", newPerson->name);
    printf("Age: %d\n", newPerson->age);
    printf("Salary: %.2f\n", newPerson->salary);

    // Free allocated memory
    free(newPerson);

    return 0;
}