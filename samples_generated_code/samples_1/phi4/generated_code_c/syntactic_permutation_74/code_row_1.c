#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status; // Status field to be set by allocator
} Person;

Person* create_person() {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (!new_person) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_person->status = 0; // Set status field to 0
    return new_person;
}

int main() {
    Person *p = create_person();
    p->id = 1;
    snprintf(p->name, sizeof(p->name), "John Doe");
    p->age = 30;

    printf("Person: %s, Age: %d, Status: %d\n", p->name, p->age, p->status);
    
    free(p); // Free the allocated memory
    return 0;
}