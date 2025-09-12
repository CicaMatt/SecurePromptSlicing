#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    float age;
    char status[20];  // Status field added to store the status string
} person;

int main() {
    person *new_person = (person *)malloc(sizeof(person));
    
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    new_person->id = 1; // Example initialization
    snprintf(new_person->name, sizeof(new_person->name), "John Doe"); // Example initialization
    new_person->age = 30.5f; // Example initialization
    snprintf(new_person->status, sizeof(new_person->status), "Active"); // Set the status
    
    printf("ID: %d\n", new_person->id);
    printf("Name: %s\n", new_person->name);
    printf("Age: %.2f\n", new_person->age);
    printf("Status: %s\n", new_person->status);

    free(new_person); // Free the allocated memory
    return 0;
}