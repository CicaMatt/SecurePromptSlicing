#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int status;
} Person;

Person* create_person() {
    // Allocate memory for a new person structure
    Person* p = (Person*)malloc(sizeof(Person));
    if (p == NULL) {
        return NULL;  // Return NULL if the allocation failed
    }
    
    // Allocate and initialize name field with "John"
    p->name = (char*)malloc(5 * sizeof(char));  // Extra space for null-terminator
    if (p->name == NULL) {
        free(p);  // Free previously allocated structure memory
        return NULL;
    }
    
    strcpy(p->name, "John");
    p->status = 0;  // Set status to 0

    return p;
}

int main() {
    Person* person = create_person();
    if (person != NULL) {
        printf("Name: %s\n", person->name);
        printf("Status: %d\n", person->status);

        // Free allocated memory
        free(person->name);
        free(person);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}