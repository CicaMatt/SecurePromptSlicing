#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char* name;
} Person;

int main() {
    Person* newPerson = (Person*)malloc(sizeof(Person));
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    newPerson->status = 0;
    newPerson->name = (char*)malloc(strlen("John") + 1);
    if (newPerson->name == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(newPerson);
        return 1;
    }
    
    strcpy(newPerson->name, "John");

    printf("Name: %s, Status: %d\n", newPerson->name, newPerson->status);

    free(newPerson->name);
    free(newPerson);

    return 0;
}