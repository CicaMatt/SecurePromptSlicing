#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status; // Status field
} Person;

Person* create_person() {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    new_person->status = 0; // Set the status to 0
    return new_person;
}

int main() {
    Person *p = create_person();
    if (p != NULL) {
        printf("Person created with status: %d\n", p->status);
        free(p); // Free allocated memory
    }
    return 0;
}