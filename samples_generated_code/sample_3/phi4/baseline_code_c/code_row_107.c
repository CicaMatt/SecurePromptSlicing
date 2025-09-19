#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char *name;
} Person;

int main() {
    Person *person = (Person *)malloc(sizeof(Person));
    
    if (person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    person->status = 0;
    person->name = (char *)malloc(5);
    
    if (person->name == NULL) {
        free(person);
        fprintf(stderr, "Memory allocation for name failed\n");
        return 1;
    }

    strcpy(person->name, "John");

    printf("Person status: %d\n", person->status);
    printf("Person name: %s\n", person->name);

    // Clean up
    free(person->name);
    free(person);

    return 0;
}