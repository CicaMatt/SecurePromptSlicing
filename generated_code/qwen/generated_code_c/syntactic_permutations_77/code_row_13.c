#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char *name;
} Person;

Person* create_person() {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        return NULL; // Memory allocation failed
    }
    new_person->status = 0;
    new_person->name = malloc(strlen("John") + 1);
    if (new_person->name == NULL) {
        free(new_person); // Free previously allocated memory for person
        return NULL; // Memory allocation failed
    }
    strcpy(new_person->name, "John");
    return new_person;
}

int main() {
    Person *john = create_person();
    if (john != NULL) {
        printf("Person created: Name - %s, Status - %d\n", john->name, john->status);
        free(john->name); // Free allocated memory for name
        free(john); // Free allocated memory for person
    } else {
        printf("Failed to create person.\n");
    }
    return 0;
}