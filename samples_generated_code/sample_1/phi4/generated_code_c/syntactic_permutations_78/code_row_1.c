#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    double salary;
    int status; // Status set to 0 on creation
} Person;

Person* create_person(int id, const char* name, int age, double salary) {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_person->id = id;
    snprintf(new_person->name, sizeof(new_person->name), "%s", name);
    new_person->age = age;
    new_person->salary = salary;
    new_person->status = 0; // Set status to 0

    return new_person;
}

int main() {
    Person *p1 = create_person(1, "John Doe", 30, 50000.50);
    
    printf("Person ID: %d\n", p1->id);
    printf("Name: %s\n", p1->name);
    printf("Age: %d\n", p1->age);
    printf("Salary: %.2f\n", p1->salary);
    printf("Status: %d\n", p1->status);

    free(p1); // Free allocated memory

    return 0;
}