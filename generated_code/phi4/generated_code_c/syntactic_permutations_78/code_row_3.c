#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
} Person;

int main() {
    // Allocate memory for a new person
    Person *newPerson = (Person *)malloc(sizeof(Person));
    
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Set the status to 0
    newPerson->status = 0;

    printf("New person created with status: %d\n", newPerson->status);
    
    // Free allocated memory
    free(newPerson);

    return 0;
}