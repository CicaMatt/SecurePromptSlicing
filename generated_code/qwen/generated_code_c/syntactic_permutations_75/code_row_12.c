#include <stdlib.h>

typedef struct {
    int status;
} person;

person* create_person() {
    person* new_person = (person*)malloc(sizeof(person));
    if (new_person != NULL) {
        new_person->status = 0;
    }
    return new_person;
}

int main() {
    person* my_person = create_person();
    free(my_person);
    return 0;
}