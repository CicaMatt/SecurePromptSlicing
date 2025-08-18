#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
} Person;

int main() {
    // Allocate memory for a new person
    Person *p = (Person *)malloc(sizeof(Person));
    
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Initialize the status to 0
    p->id = 0; // Assuming 'id' is used as a status placeholder here

    printf("Person created with ID: %d\n", p->id);

    // Free allocated memory
    free(p);
    
    return 0;
}