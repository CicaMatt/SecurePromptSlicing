#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status; // 0 means not initialized, other values can be used for different statuses.
} Person;

Person* allocateNewPerson() {
    Person* newPerson = (Person*)malloc(sizeof(Person));
    if (newPerson == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    newPerson->status = 0;
    return newPerson;
}

int main() {
    Person* person1 = allocateNewPerson();
    printf("Allocated a new person with status: %d\n", person1->status);

    // Example of setting values after allocation
    person1->id = 1;
    snprintf(person1->name, sizeof(person1->name), "John Doe");
    person1->age = 30;
    person1->status = 1; // Set status to 1 indicating initialized

    printf("Person ID: %d\n", person1->id);
    printf("Name: %s\n", person1->name);
    printf("Age: %d\n", person1->age);
    printf("Status: %d\n", person1->status);

    free(person1); // Don't forget to free the allocated memory
    return 0;
}