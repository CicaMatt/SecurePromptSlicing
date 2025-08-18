#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char *name;
} Person;

int main() {
    Person *newPerson = (Person *)malloc(sizeof(Person));
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    newPerson->status = 0;
    newPerson->name = (char *)malloc(1); // Allocate space for the null terminator
    if (newPerson->name == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(newPerson);
        return 1;
    }
    strcpy(newPerson->name, "");

    printf("Person created with status: %d and name: '%s'\n", newPerson->status, newPerson->name);

    // Free allocated memory
    free(newPerson->name);
    free(newPerson);

    return 0;
}