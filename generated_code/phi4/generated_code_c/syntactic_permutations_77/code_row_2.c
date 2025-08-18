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
    new_person->name = (char*)malloc(5); // Allocate memory for "John" + null terminator
    
    if (new_person->name != NULL) {
        strcpy(new_person->name, "John");
    } else {
        free(new_person);
        return NULL; // Memory allocation failed
    }
    
    return new_person;
}

int main() {
    Person *person = create_person();
    if (person == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return 1;
    }

    printf("Person status: %d\n", person->status);
    printf("Person name: %s\n", person->name);

    // Free the allocated memory
    free(person->name);
    free(person);

    return 0;
}