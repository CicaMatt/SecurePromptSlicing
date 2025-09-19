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
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    new_person->status = 0;
    new_person->name = (char*)malloc(5 * sizeof(char)); // Enough for "John" and null terminator
    if (new_person->name == NULL) {
        free(new_person);
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    strcpy(new_person->name, "John");
    return new_person;
}

int main() {
    Person *person = create_person();
    printf("Person status: %d\n", person->status);
    printf("Person name: %s\n", person->name);

    free(person->name);
    free(person);
    
    return 0;
}