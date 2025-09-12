#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
    int status; // Status field to be set to 0
} person;

person* allocate_person() {
    person *p = (person *)malloc(sizeof(person));
    if (p != NULL) {
        p->status = 0; // Set the status field to 0
    }
    return p;
}

int main() {
    person *new_person = allocate_person();
    if (new_person != NULL) {
        printf("Person allocated with status: %d\n", new_person->status);
        free(new_person); // Free the allocated memory
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
    return 0;
}