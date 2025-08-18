#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int status;
} Person;

Person* create_person() {
    Person* new_person = (Person*)malloc(sizeof(Person));
    if (new_person != NULL) {
        new_person->status = 0;
    }
    return new_person;
}

int main() {
    Person* person = create_person();
    if (person != NULL) {
        printf("Person created with status: %d\n", person->status);
        free(person);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}