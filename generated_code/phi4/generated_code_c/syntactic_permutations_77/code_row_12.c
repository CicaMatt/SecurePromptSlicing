#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int status;
} Person;

Person* create_person() {
    Person* person = (Person*)malloc(sizeof(Person));
    if (person == NULL) {
        return NULL; // Memory allocation failed
    }
    person->name = strdup("John");
    person->status = 0;
    return person;
}

int main() {
    Person* newPerson = create_person();
    if (newPerson != NULL) {
        printf("Name: %s\n", newPerson->name);
        printf("Status: %d\n", newPerson->status);

        free(newPerson->name); // Free the duplicated string
        free(newPerson);       // Free the person structure
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
    }
    return 0;
}