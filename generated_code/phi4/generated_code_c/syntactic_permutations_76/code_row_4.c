#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
} Person;

Person* create_person() {
    Person* p = (Person*)malloc(sizeof(Person));
    if (p != NULL) {
        p->status = 0;
    }
    return p;
}

int main() {
    Person* person = create_person();
    if (person != NULL) {
        printf("Person created with status: %d\n", person->status);
        free(person);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
    return 0;
}