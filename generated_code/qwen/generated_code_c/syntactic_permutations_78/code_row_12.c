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
    free(person);
    return 0;
}