#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int status;
} Person;

int main() {
    Person *newPerson = (Person *)malloc(sizeof(Person));
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    newPerson->name = malloc(strlen("John") + 1);
    if (newPerson->name == NULL) {
        free(newPerson);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    strcpy(newPerson->name, "John");
    newPerson->status = 0;

    printf("Name: %s, Status: %d\n", newPerson->name, newPerson->status);

    free(newPerson->name);
    free(newPerson);

    return 0;
}