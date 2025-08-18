#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status; // Status field as specified in the prompt
} Person;

Person* allocate_person() {
    Person *new_person = (Person *)malloc(sizeof(Person));
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    new_person->status = 0; // Setting status field to 0 as specified
    return new_person;
}

int main() {
    Person *p = allocate_person();
    printf("Person allocated with status: %d\n", p->status);

    free(p); // Free the allocated memory

    return 0;
}