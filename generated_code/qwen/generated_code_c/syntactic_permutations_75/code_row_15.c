#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
} person;

int main() {
    person *newPerson = (person *)malloc(sizeof(person));
    
    if (newPerson == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Example usage: initializing the new person
    snprintf(newPerson->name, sizeof(newPerson->name), "John Doe");
    newPerson->age = 30;

    printf("Name: %s\n", newPerson->name);
    printf("Age: %d\n", newPerson->age);

    // Freeing the allocated memory
    free(newPerson);

    return 0;
}