#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
} Person;

Person* create_person() {
    Person *new_person = (Person*) malloc(sizeof(Person));
    if (new_person != NULL) {
        new_person->status = 0;
    }
    return new_person;
}

int main() {
    Person *p = create_person();
    if (p != NULL) {
        printf("New person created with status: %d\n", p->status);
        free(p);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
    return 0;
}