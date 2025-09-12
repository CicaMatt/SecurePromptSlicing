#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
} Person;

int main() {
    // Allocate memory for one Person
    Person *person = (Person *)malloc(sizeof(Person));
    
    if (person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Set the status to 0
    person->status = 0;

    printf("Status: %d\n", person->status);

    // Free allocated memory
    free(person);
    
    return 0;
}