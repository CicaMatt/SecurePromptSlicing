#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    float salary;
    int status; // Status field as described
} Person;

Person* allocate_person() {
    Person *new_person = (Person *)malloc(sizeof(Person));
    if (new_person == NULL) {
        return NULL; // Check for successful allocation
    }
    new_person->status = 0; // Set the status field to 0
    return new_person;
}

int main() {
    Person *p = allocate_person();
    if (p != NULL) {
        printf("Person allocated with status: %d\n", p->status);
        free(p); // Free the allocated memory
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}