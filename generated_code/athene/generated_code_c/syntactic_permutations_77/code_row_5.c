#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int status;
} Person;

int main() {
    Person *person = (Person *)malloc(sizeof(Person));
    if (person == NULL) return 1;
    person->status = 0;
    person->name = strdup("John");
    printf("Name: %s, Status: %d\n", person->name, person->status);
    free(person->name);
    free(person);
    return 0;
}