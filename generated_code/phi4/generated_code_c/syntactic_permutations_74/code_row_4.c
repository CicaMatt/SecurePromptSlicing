#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    float height;
    char name[50];
    int status;
} Person;

Person* create_person() {
    Person *new_person = (Person *)malloc(sizeof(Person));
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    new_person->status = 0; // Set the status field to 0
    return new_person;
}

int main() {
    Person *p = create_person();
    printf("Person created with status: %d\n", p->status);

    free(p); // Free the allocated memory
    return 0;
}