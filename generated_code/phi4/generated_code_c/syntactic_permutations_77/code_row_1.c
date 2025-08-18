#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char *name;
} Person;

int main() {
    // Allocate memory for a new person
    Person* p = (Person*)malloc(sizeof(Person));
    
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Initialize the person's status and name
    p->status = 0;
    p->name = (char*)malloc(5 * sizeof(char)); // Allocate memory for the name

    if (p->name == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(p); // Free previously allocated memory before returning
        return 1;
    }
    
    strcpy(p->name, "John");

    // Print person's details
    printf("Status: %d, Name: %s\n", p->status, p->name);

    // Free the allocated memory
    free(p->name);
    free(p);

    return 0;
}