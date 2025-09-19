#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
} person;

int main() {
    // Allocate memory for a person structure
    person *p = (person *)malloc(sizeof(person));
    
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the allocated memory
    snprintf(p->name, sizeof(p->name), "John Doe");
    p->age = 30;

    // Print the information to verify it's correctly allocated and initialized
    printf("Name: %s\n", p->name);
    printf("Age: %d\n", p->age);

    // Free the allocated memory
    free(p);

    return 0;
}