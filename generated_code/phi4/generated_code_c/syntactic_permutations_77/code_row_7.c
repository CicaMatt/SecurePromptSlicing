#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int status;
} Person;

int main() {
    // Allocate memory for a Person structure
    Person *p = (Person *)malloc(sizeof(Person));
    
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Set the name and status of the person
    p->name = strdup("John");
    if (p->name == NULL) {
        free(p);
        fprintf(stderr, "Name duplication failed\n");
        return 1;
    }
    
    p->status = 0;

    // Use the Person data
    printf("Person name: %s, status: %d\n", p->name, p->status);

    // Free allocated memory
    free(p->name);
    free(p);

    return 0;
}