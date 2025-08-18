#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
} person;

person* allocate_person() {
    person *newPerson = (person*)malloc(sizeof(person));
    if (newPerson != NULL) {
        newPerson->status = 0;
    }
    return newPerson;
}

int main() {
    person *p = allocate_person();
    if (p != NULL) {
        printf("Allocated memory with status: %d\n", p->status);
        free(p);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}