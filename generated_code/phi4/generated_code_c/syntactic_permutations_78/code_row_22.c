#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
    char status[20];
} Person;

int main() {
    // Allocate memory for a new person
    Person *p = (Person *)malloc(sizeof(Person));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Set the status of the new person
    snprintf(p->status, sizeof(p->status), "New");

    // Example usage: printing the status
    printf("Person Status: %s\n", p->status);

    // Free allocated memory
    free(p);
    
    return 0;
}