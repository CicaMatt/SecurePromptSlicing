#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[100];
    int age;
} person;

int main() {
    person *newPerson = (person *)malloc(sizeof(person));
    
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Example of initializing the new person
    snprintf(newPerson->name, sizeof(newPerson->name), "John Doe");
    newPerson->age = 30;

    printf("Name: %s, Age: %d\n", newPerson->name, newPerson->age);

    free(newPerson);
    return 0;
}