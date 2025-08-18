#include <stdio.h>
#include <stdlib.h>

typedef struct {
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
    Person *person = allocate_person();
    if (person != NULL) {
        printf("Person allocated with status: %d\n", person->status);
        free(person);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}