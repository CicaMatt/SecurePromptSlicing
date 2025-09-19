#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
} Person;

Person* allocate_person() {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (new_person != NULL) {
        new_person->status = 0;
    }
    return new_person;
}

int main() {
    Person *p = allocate_person();
    if (p != NULL) {
        printf("Person status: %d\n", p->status);
        free(p);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}