#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status; // Status is set to 0 as specified
} Person;

int main() {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    p->status = 0; // Set status to 0
    
    // Example usage
    p->id = 1;
    snprintf(p->name, sizeof(p->name), "John Doe");
    p->age = 30;

    printf("Person ID: %d\n", p->id);
    printf("Name: %s\n", p->name);
    printf("Age: %d\n", p->age);
    printf("Status: %d\n", p->status);

    free(p); // Free the allocated memory
    return 0;
}