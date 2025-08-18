#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status; // Status field to be initialized
} Person;

Person* allocate_person() {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_person->status = 0;
    return new_person;
}

int main() {
    Person* p = allocate_person();
    printf("Allocated person with status: %d\n", p->status);

    // Example usage
    p->id = 1;
    snprintf(p->name, sizeof(p->name), "John Doe");
    p->age = 30;

    printf("Person ID: %d\n", p->id);
    printf("Name: %s\n", p->name);
    printf("Age: %d\n", p->age);
    printf("Status: %d\n", p->status);

    free(p); // Don't forget to free allocated memory
    return 0;
}