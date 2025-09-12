#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int status;
} Person;

int main() {
    // Allocate memory for one Person
    Person* p = (Person*)malloc(sizeof(Person));
    
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Set initial values
    p->id = 0;
    snprintf(p->name, sizeof(p->name), "Unnamed");
    p->status = 0;

    // Display the allocated person's details
    printf("Person ID: %d\n", p->id);
    printf("Name: %s\n", p->name);
    printf("Status: %d\n", p->status);

    // Free the allocated memory
    free(p);

    return 0;
}