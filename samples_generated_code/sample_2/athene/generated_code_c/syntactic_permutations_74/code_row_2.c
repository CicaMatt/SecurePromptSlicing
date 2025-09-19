#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status;
} Person;

Person* allocate_person() {
    Person *p = (Person*)malloc(sizeof(Person));
    if (p != NULL) {
        p->status = 0;
    }
    return p;
}

int main() {
    Person *new_person = allocate_person();
    if (new_person != NULL) {
        printf("Person allocated with status: %d\n", new_person->status);
        free(new_person);
    }
    return 0;
}