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
        exit(1);
    }
    person->status = 0;
    person->name = (char *)malloc(strlen("John") + 1);
    if (person->name == NULL) {
        free(person);
        exit(1);
    }
    strcpy(person->name, "John");
    printf("Status: %d\nName: %s\n", person->status, person->name);
    free(person->name);
    free(person);
    return 0;
}