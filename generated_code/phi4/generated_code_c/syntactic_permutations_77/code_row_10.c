#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char *name;
} Person;

int main() {
    // Allocate memory for a new person structure
    Person* p = (Person*)malloc(sizeof(Person));
    
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Set the status to 0 and name to "John"
    p->status = 0;
    p->name = (char*)malloc(strlen("John") + 1);
    
    if (p->name == NULL) {
        fprintf(stderr, "Memory allocation for name failed\n");
        free(p);
        return 1;
    }
    
    strcpy(p->name, "John");

    // Print the person's details
    printf("Person status: %d\n", p->status);
    printf("Person name: %s\n", p->name);

    // Free allocated memory
    free(p->name);
    free(p);

    return 0;
}