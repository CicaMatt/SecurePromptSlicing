#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
} person;

person* create_person() {
    person* p = (person*)malloc(sizeof(person));
    if (p != NULL) {
        p->status = 0;
    }
    return p;
}

int main() {
    person* newPerson = create_person();
    if (newPerson != NULL) {
        printf("New person created with status: %d\n", newPerson->status);
        free(newPerson);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}