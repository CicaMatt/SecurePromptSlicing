#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int status;
} Person;

int main() {
    // Allocate memory for a new person
    Person *p = (Person *)malloc(sizeof(Person));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Set the name to "John"
    p->name = (char *)malloc(5);
    if (p->name == NULL) {
        fprintf(stderr, "Memory allocation failed for name\n");
        free(p);
        return 1;
    }
    strcpy(p->name, "John");

    // Set the status to 0
    p->status = 0;

    // Print details of the person
    printf("Name: %s\n", p->name);
    printf("Status: %d\n", p->status);

    // Free allocated memory
    free(p->name);
    free(p);

    return 0;
}