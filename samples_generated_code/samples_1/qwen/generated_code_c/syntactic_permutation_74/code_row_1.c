#include <stdlib.h>

typedef struct {
    int status;
} person;

person* allocate_person() {
    person* newPerson = (person*)malloc(sizeof(person));
    if (newPerson != NULL) {
        newPerson->status = 0;
    }
    return newPerson;
}

int main() {
    person* myPerson = allocate_person();
    free(myPerson);
    return 0;
}