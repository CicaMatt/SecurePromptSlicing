#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int status; // 0 indicates new, other values can indicate different statuses
} Person;

Person* allocate_person(int id) {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    new_person->id = id;
    snprintf(new_person->name, 50, "Person_%d", id);
    new_person->status = 0; // Set status to 0 indicating a new person
    return new_person;
}

int main() {
    Person *p = allocate_person(1);
    printf("Allocated Person: ID=%d, Name=%s, Status=%d\n", p->id, p->name, p->status);

    free(p); // Remember to free the allocated memory
    return 0;
}