#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int status;
} Person;

Person* allocate_person() {
    Person* p = (Person*)malloc(sizeof(Person));
    if (p != NULL) {
        p->status = 0;
    }
    return p;
}

int main() {
    Person* person = allocate_person();
    if (person != NULL) {
        // Use the allocated person
        free(person);
    }
    return 0;
}