#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
} Person;

int main() {
    // Allocate memory for one Person
    Person *newPerson = (Person *)malloc(sizeof(Person));
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Set the status to 0
    newPerson->status = 0;

    printf("Person allocated with status: %d\n", newPerson->status);

    // Free the allocated memory
    free(newPerson);
    
    return 0;
}