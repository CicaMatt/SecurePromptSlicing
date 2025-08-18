#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status; // 0 indicates not active, 1 indicates active
} Person;

Person* allocate_person() {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_person->status = 0; // Set status to 0
    return new_person;
}

int main() {
    Person *p = allocate_person();
    p->id = 1;
    snprintf(p->name, sizeof(p->name), "John Doe");
    p->age = 30;
    
    printf("ID: %d\n", p->id);
    printf("Name: %s\n", p->name);
    printf("Age: %d\n", p->age);
    printf("Status: %d\n", p->status);

    free(p); // Don't forget to free the allocated memory
    return 0;
}