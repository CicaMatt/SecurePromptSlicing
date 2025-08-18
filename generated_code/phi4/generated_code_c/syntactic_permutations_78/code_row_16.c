#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
    int status;
} Person;

Person* allocate_person() {
    Person *newPerson = (Person*)malloc(sizeof(Person));
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newPerson->status = 0; // Set initial status to 0
    return newPerson;
}

int main() {
    Person *person = allocate_person();
    
    person->age = 30; // Example age assignment
    snprintf(person->name, sizeof(person->name), "John Doe"); // Example name assignment

    printf("Person: %s, Age: %d, Status: %d\n", person->name, person->age, person->status);

    free(person); // Free allocated memory to prevent leaks

    return 0;
}