#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
    int status;
} Person;

int main() {
    // Allocate memory for one person
    Person *newPerson = (Person *)malloc(sizeof(Person));
    
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Set the status of the new person
    newPerson->status = 0; // Example: setting status to 0
    
    printf("New person allocated with status: %d\n", newPerson->status);
    
    // Free the allocated memory
    free(newPerson);
    
    return 0;
}