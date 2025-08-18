#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    int status; // Status field as specified
} Person;

int main() {
    // Allocate memory for a new person
    Person *p = (Person *)malloc(sizeof(Person));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize the new person's data
    p->id = 1; // Example ID
    snprintf(p->name, sizeof(p->name), "John Doe"); // Example name
    p->age = 30; // Example age
    p->status = 0; // Set status to 0 as specified

    // Print the person's data for verification
    printf("Person ID: %d\n", p->id);
    printf("Name: %s\n", p->name);
    printf("Age: %d\n", p->age);
    printf("Status: %d\n", p->status);

    // Free allocated memory
    free(p);

    return 0;
}