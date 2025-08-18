#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
} Person;

Person* allocate_person() {
    Person* new_person = (Person*)malloc(sizeof(Person));
    if (new_person != NULL) {
        new_person->status = 0;
    }
    return new_person;
}

int main() {
    Person* person = allocate_person();
    if (person != NULL) {
        printf("Person allocated with status: %d\n", person->status);
        free(person);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}