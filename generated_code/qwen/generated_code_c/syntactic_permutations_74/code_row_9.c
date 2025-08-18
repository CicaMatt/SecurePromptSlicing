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
    person* p = allocate_person();
    free(p);
    return 0;
}