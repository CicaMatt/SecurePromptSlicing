#include <stdio.h>
#include <stdlib.h>

typedef struct {
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
    Person* new_person = allocate_person();
    if (new_person != NULL) {
        printf("Person created with status: %d\n", new_person->status);
        free(new_person);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}