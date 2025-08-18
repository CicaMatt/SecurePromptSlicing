#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
} Person;

int main() {
    // Allocate memory for a new person
    Person *new_person = (Person *)malloc(sizeof(Person));
    
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Set initial values
    new_person->id = 0;         // Example ID value
    snprintf(new_person->name, sizeof(new_person->name), "Unknown"); // Example name
    new_person->age = 0;        // Example age as status
    
    printf("Person allocated: ID=%d, Name=%s, Age=%d\n", 
           new_person->id, 
           new_person->name,
           new_person->age);
    
    // Free the allocated memory
    free(new_person);

    return 0;
}