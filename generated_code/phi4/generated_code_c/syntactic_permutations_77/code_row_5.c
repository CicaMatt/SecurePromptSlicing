#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char name[50];
} Person;

int main() {
    // Allocate memory for one Person struct
    Person *person = (Person *)malloc(sizeof(Person));
    
    if (person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Initialize the person's status and name
    person->status = 0;
    strcpy(person->name, "John");
    
    // Print the values to verify
    printf("Status: %d\n", person->status);
    printf("Name: %s\n", person->name);
    
    // Free allocated memory
    free(person);
    
    return 0;
}