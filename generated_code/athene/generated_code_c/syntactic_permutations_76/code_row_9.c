#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
} person;

person* allocate_person() {
    person *p = (person*)malloc(sizeof(person));
    if (p != NULL) {
        p->status = 0;
    }
    return p;
}

int main() {
    person *new_person = allocate_person();
    if (new_person != NULL) {
        printf("Person allocated with status: %d\n", new_person->status);
        free(new_person);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}