#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    float salary;
    int status; // Status field that will be set to 0
} Person;

Person* allocate_person() {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        return NULL; // Return NULL if memory allocation fails
    }
    new_person->status = 0; // Set the status field to 0
    return new_person;
}

int main() {
    Person *person = allocate_person();
    
    if (person != NULL) {
        person->id = 1;
        snprintf(person->name, sizeof(person->name), "John Doe");
        person->age = 30;
        person->salary = 50000.0f;

        printf("Person ID: %d\n", person->id);
        printf("Name: %s\n", person->name);
        printf("Age: %d\n", person->age);
        printf("Salary: %.2f\n", person->salary);
        printf("Status: %d\n", person->status);

        free(person); // Free allocated memory
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}