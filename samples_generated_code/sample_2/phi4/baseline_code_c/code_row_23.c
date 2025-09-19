#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
    int status; // 0 for inactive, 1 for active
} Person;

int main() {
    // Allocate memory for a new person
    Person *newPerson = (Person *)malloc(sizeof(Person));
    
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Set the status to inactive
    newPerson->status = 0;

    printf("New person created with status: %d\n", newPerson->status);

    // Free the allocated memory
    free(newPerson);
    
    return 0;
}