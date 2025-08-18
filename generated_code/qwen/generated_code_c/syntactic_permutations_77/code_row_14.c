#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int status;
} Person;

int main() {
    Person *person = (Person *)malloc(sizeof(Person));
    if (person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    person->status = 0;
    person->name = (char *)malloc(5 * sizeof(char)); // Length of "John" + 1 for null terminator
    if (person->name == NULL) {
        free(person);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    strcpy(person->name, "John");

    printf("Name: %s, Status: %d\n", person->name, person->status);

    free(person->name);
    free(person);

    return 0;
}