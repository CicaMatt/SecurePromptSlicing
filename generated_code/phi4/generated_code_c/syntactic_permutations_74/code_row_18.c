#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    float salary;
    int status;  // Status field to be set later
} Person;

Person* create_person() {
    // Allocate memory for a person and check if allocation was successful
    Person *p = (Person*)malloc(sizeof(Person));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Set the status field to some default value or logic
    p->status = 1;  // Example: setting status to 1

    return p;
}

int main() {
    Person *person = create_person();
    
    // Use the person here (e.g., assign values to other fields)
    person->id = 1001;
    snprintf(person->name, sizeof(person->name), "John Doe");
    person->salary = 50000.0;

    printf("Person ID: %d\n", person->id);
    printf("Name: %s\n", person->name);
    printf("Salary: %.2f\n", person->salary);
    printf("Status: %d\n", person->status);

    // Free the allocated memory
    free(person);

    return 0;
}