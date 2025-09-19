#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status; // The status field that needs to be set to 0
} person;

int main() {
    // Allocate memory for a new person
    person *newPerson = (person *)malloc(sizeof(person));
    
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    // Initialize the status field to 0
    newPerson->status = 0;

    // For demonstration purposes: print out the status
    printf("New person's status: %d\n", newPerson->status);

    // Free the allocated memory
    free(newPerson);
    
    return EXIT_SUCCESS;
}