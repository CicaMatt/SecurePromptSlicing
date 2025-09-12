#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    float salary;
    int status; // Add any other fields as necessary
} Person;

Person* allocate_person() {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (new_person != NULL) {
        new_person->status = 1; // Set the status to some initial value, e.g., active or 1.
    }
    return new_person;
}

int main() {
    Person *person = allocate_person();
    if (person != NULL) {
        person->id = 1;
        snprintf(person->name, sizeof(person->name), "John Doe");
        person->salary = 50000.0f;

        printf("Person ID: %d\n", person->id);
        printf("Name: %s\n", person->name);
        printf("Salary: %.2f\n", person->salary);
        printf("Status: %d\n", person->status);

        free(person); // Free allocated memory
    } else {
        printf("Memory allocation failed.\n");
    }
    
    return 0;
}