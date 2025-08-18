#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
} Person;

int main() {
    Person *newPerson = (Person *)malloc(sizeof(Person));

    if (newPerson == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Example of initializing the new person
    snprintf(newPerson->name, sizeof(newPerson->name), "John Doe");
    newPerson->age = 30;

    printf("Name: %s, Age: %d\n", newPerson->name, newPerson->age);

    free(newPerson);
    return 0;
}