#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int age;
    char *name;
} Person;

int main() {
    Person *person = (Person *)malloc(sizeof(Person));
    if (person == NULL) {
        return 1; // Memory allocation failed
    }

    person->age = 0;
    person->name = (char *)malloc(5 * sizeof(char)); // Allocate memory for "John" + null terminator
    if (person->name == NULL) {
        free(person); // Free previously allocated memory before returning
        return 1; // Memory allocation failed
    }

    strcpy(person->name, "John");

    printf("Name: %s\nAge: %d\n", person->name, person->age);

    free(person->name);
    free(person);

    return 0;
}