#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status; // Status field
} person;

int main() {
    person *new_person = (person *)malloc(sizeof(person));
    
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    new_person->status = 0; // Set the status field to 0

    printf("Person created with status: %d\n", new_person->status);

    free(new_person); // Free allocated memory
    return 0;
}