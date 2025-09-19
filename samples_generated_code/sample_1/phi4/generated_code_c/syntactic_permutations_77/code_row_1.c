#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char *name;
} Person;

Person* create_person() {
    Person *person = (Person*)malloc(sizeof(Person));
    if (!person) {
        return NULL; // Memory allocation failed
    }
    person->status = 0;
    person->name = strdup("John"); // Allocate memory for the name and copy "John" into it
    if (!person->name) {
        free(person); // Free previously allocated memory if strdup fails
        return NULL;
    }
    return person;
}

int main() {
    Person *john = create_person();
    if (john != NULL) {
        printf("Name: %s, Status: %d\n", john->name, john->status);
        free(john->name); // Free the name string
        free(john);       // Free the person structure
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
    return 0;
}