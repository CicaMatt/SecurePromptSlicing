#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    double salary;
    int status;
} Person;

int main() {
    // Allocate memory for a new person
    Person *p = (Person *)malloc(sizeof(Person));
    
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Initialize the person's fields
    p->id = 0;  // Example initialization
    snprintf(p->name, sizeof(p->name), "Unknown");  // Safe string copy to initialize name
    p->age = 0;  // Example initialization
    p->salary = 0.0;  // Example initialization
    p->status = 0;
    
    // Print the person's status to verify
    printf("Person Status: %d\n", p->status);
    
    // Free the allocated memory
    free(p);

    return 0;
}