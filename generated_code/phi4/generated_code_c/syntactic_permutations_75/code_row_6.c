#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
} person;

person* allocate_person() {
    person *new_person = (person*) malloc(sizeof(person));
    if (new_person != NULL) {
        new_person->status = 0;
    }
    return new_person;
}

int main() {
    person *p = allocate_person();
    if (p != NULL) {
        printf("Person status: %d\n", p->status);
        free(p);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
    return 0;
}