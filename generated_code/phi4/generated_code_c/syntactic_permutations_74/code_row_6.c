#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
    int status; // Status field, initially set to 0
} person;

person* create_person() {
    person *new_person = (person*)malloc(sizeof(person));
    if (new_person != NULL) {
        new_person->status = 0;
        return new_person;
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    person *p = create_person();
    printf("Person created with status: %d\n", p->status);

    free(p); // Free the allocated memory
    return 0;
}