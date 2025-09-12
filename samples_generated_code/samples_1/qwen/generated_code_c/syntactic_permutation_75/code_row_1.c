#include <stdlib.h>

typedef struct {
    int status;
} person;

person* allocate_person() {
    person* new_person = (person*)malloc(sizeof(person));
    if (new_person != NULL) {
        new_person->status = 0;
    }
    return new_person;
}

int main() {
    person* my_person = allocate_person();
    free(my_person);
    return 0;
}