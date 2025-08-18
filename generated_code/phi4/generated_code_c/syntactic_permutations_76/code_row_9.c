#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status; // 0 means unassigned, otherwise assigned
} Person;

Person* allocate_person() {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_person->status = 0;
    return new_person;
}

int main() {
    Person* p = allocate_person();
    printf("New person allocated with status: %d\n", p->status);
    
    // Clean up
    free(p);

    return 0;
}