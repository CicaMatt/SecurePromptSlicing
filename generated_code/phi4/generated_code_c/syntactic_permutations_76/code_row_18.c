#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
    int status;
} Person;

Person* create_person() {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    p->status = 0; // Set default status
    return p;
}

int main() {
    Person *new_person = create_person();
    new_person->age = 30;
    snprintf(new_person->name, sizeof(new_person->name), "John Doe");

    printf("Person: %s, Age: %d, Status: %d\n", new_person->name, new_person->age, new_person->status);

    free(new_person);
    return 0;
}