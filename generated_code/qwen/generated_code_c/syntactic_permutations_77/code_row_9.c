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
        return 1;
    }
    person->status = 0;
    person->name = malloc(5); // Length of "John" + 1 for null terminator
    if (person->name == NULL) {
        free(person);
        return 1;
    }
    strcpy(person->name, "John");
    
    printf("Name: %s, Status: %d\n", person->name, person->status);

    free(person->name);
    free(person);
    return 0;
}