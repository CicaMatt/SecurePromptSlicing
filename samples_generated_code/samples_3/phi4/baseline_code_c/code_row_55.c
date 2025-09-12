#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int status;
} person;

person* create_person() {
    person *new_person = (person *)malloc(sizeof(person));
    if (new_person == NULL) {
        return NULL; // Handle memory allocation failure
    }
    new_person->status = 0; // Set the status field to 0
    return new_person;
}

int main() {
    person *p = create_person();
    if (p != NULL) {
        printf("Person created with status: %d\n", p->status);
        free(p); // Free allocated memory when done
    } else {
        printf("Failed to allocate memory for a person.\n");
    }
    return 0;
}