#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
} Person;

int main() {
    // Allocate memory for one person
    Person *newPerson = (Person *)malloc(sizeof(Person));
    
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Initialize the newly allocated person's data
    snprintf(newPerson->name, sizeof(newPerson->name), "John Doe");
    newPerson->age = 30;

    // Use the person's data
    printf("Name: %s\n", newPerson->name);
    printf("Age: %d\n", newPerson->age);

    // Free allocated memory
    free(newPerson);

    return 0;
}