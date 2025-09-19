#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status; // 1 for active, 0 for inactive
} Person;

Person* create_person() {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p == NULL) {
        return NULL;
    }
    p->status = 0; // Set status to inactive initially
    return p;
}

int main() {
    Person *newPerson = create_person();
    if (newPerson != NULL) {
        newPerson->id = 1;
        snprintf(newPerson->name, sizeof(newPerson->name), "John Doe");
        newPerson->age = 30;

        printf("ID: %d\n", newPerson->id);
        printf("Name: %s\n", newPerson->name);
        printf("Age: %d\n", newPerson->age);
        printf("Status: %d\n", newPerson->status);

        free(newPerson); // Free allocated memory
    } else {
        fprintf(stderr, "Memory allocation failed!\n");
    }

    return 0;
}