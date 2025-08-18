#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status; // New field for status
} Person;

Person* allocate_new_person() {
    Person *new_person = (Person*) malloc(sizeof(Person));
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    new_person->status = 0; // Set the status to 0
    return new_person;
}

int main() {
    Person *p = allocate_new_person();
    
    printf("New person allocated with status: %d\n", p->status);

    free(p); // Free the allocated memory
    return 0;
}