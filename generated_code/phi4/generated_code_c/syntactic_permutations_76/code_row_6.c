#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
} Person;

Person* allocate_person() {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        return NULL; // Memory allocation failed
    }
    
    new_person->id = 0;
    new_person->age = 0;
    new_person->name[0] = '\0'; // Initialize name as an empty string

    return new_person;
}

int main() {
    Person *p = allocate_person();
    if (p != NULL) {
        printf("Person allocated with ID: %d, Name: '%s', Age: %d\n", p->id, p->name, p->age);
        free(p); // Free the allocated memory
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}