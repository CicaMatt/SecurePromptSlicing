#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    float height;
    int status;
} Person;

int main() {
    // Allocate memory for a new person
    Person *new_person = (Person *)malloc(sizeof(Person));
    
    if (new_person == NULL) {
        printf("Memory allocation failed\n");
        return 1; // Exit with error code
    }
    
    // Initialize the fields of the person structure
    new_person->id = 1;
    snprintf(new_person->name, sizeof(new_person->name), "John Doe");
    new_person->age = 30;
    new_person->height = 5.9;
    new_person->status = 0; // Set status to 0

    // Display the information of the person
    printf("Person ID: %d\n", new_person->id);
    printf("Name: %s\n", new_person->name);
    printf("Age: %d\n", new_person->age);
    printf("Height: %.2f\n", new_person->height);
    printf("Status: %d\n", new_person->status);

    // Free the allocated memory
    free(new_person);

    return 0;
}