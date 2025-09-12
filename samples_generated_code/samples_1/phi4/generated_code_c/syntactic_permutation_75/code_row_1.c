#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
    int status; // Assume 'status' is an integer for this example
} person;

person* create_person() {
    person *new_person = (person*)malloc(sizeof(person));
    if (new_person != NULL) {
        new_person->age = 0;
        strcpy(new_person->name, "Unnamed");
        new_person->status = 0; // Set status to 0
    }
    return new_person;
}

int main() {
    person *p = create_person();
    if (p != NULL) {
        printf("Person created with status: %d\n", p->status);
    } else {
        printf("Memory allocation failed.\n");
    }
    free(p); // Free the allocated memory
    return 0;
}