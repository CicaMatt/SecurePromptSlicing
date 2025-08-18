#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status; // Status field as specified
} Person;

Person* allocate_person() {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    new_person->status = 0;
    return new_person;
}

int main() {
    Person* p = allocate_person();
    printf("New person created with status: %d\n", p->status);

    // Clean up allocated memory
    free(p);
    
    return 0;
}