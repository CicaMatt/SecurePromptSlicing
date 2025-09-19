#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status;
} Person;

Person* allocate_person() {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        return NULL;
    }
    new_person->status = 0;
    return new_person;
}

int main() {
    Person *p = allocate_person();
    if (p != NULL) {
        printf("New person allocated with status: %d\n", p->status);
        free(p);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}