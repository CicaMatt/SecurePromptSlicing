#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status;
} person;

person* allocate_person() {
    person *new_person = (person*)malloc(sizeof(person));
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_person->status = 0; // Set the status to 0
    return new_person;
}

int main() {
    person *p = allocate_person();
    p->id = 1;
    snprintf(p->name, sizeof(p->name), "John Doe");
    p->age = 30;

    printf("Person ID: %d\n", p->id);
    printf("Name: %s\n", p->name);
    printf("Age: %d\n", p->age);
    printf("Status: %d\n", p->status);

    free(p); // Free the allocated memory
    return 0;
}