#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char name[50];
} Person;

int main() {
    Person *person = (Person *)malloc(sizeof(Person));
    if (person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    person->status = 0;
    strcpy(person->name, "John");

    printf("Status: %d\n", person->status);
    printf("Name: %s\n", person->name);

    free(person);
    return 0;
}