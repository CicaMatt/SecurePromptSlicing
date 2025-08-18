#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int status;
} Person;

Person* create_person() {
    // Allocate memory for a new person structure
    Person* p = (Person*)malloc(sizeof(Person));
    if (!p) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    // Allocate memory and set the name to "John"
    p->name = (char*)malloc(5 * sizeof(char)); // 4 characters + null terminator
    if (!p->name) {
        free(p); // Clean up already allocated person structure before exiting
        fprintf(stderr, "Memory allocation for name failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(p->name, "John");

    // Set the status to 0
    p->status = 0;

    return p;
}

void free_person(Person* p) {
    if (p) {
        free(p->name); // Free allocated memory for name first
        free(p);       // Then free the person structure itself
    }
}

int main() {
    Person* person = create_person();
    
    printf("Name: %s, Status: %d\n", person->name, person->status);
    
    free_person(person);
    return 0;
}