#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    float salary;
    int status; // Status field initialized to 0
} Person;

Person* allocate_person() {
    // Allocate memory for a new person
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    // Initialize the status field to 0
    new_person->status = 0;

    return new_person;
}

int main() {
    Person *p = allocate_person();
    printf("Person ID: %d\n", p->id);
    printf("Person Name: %s\n", p->name);
    printf("Person Age: %d\n", p->age);
    printf("Person Salary: %.2f\n", p->salary);
    printf("Person Status: %d\n", p->status);

    free(p); // Free the allocated memory
    return 0;
}