#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
} Person;

int main() {
    // Allocate memory for one Person structure
    Person *person = (Person *)malloc(sizeof(Person));
    
    if (person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    // Set the person's name to "John"
    strcpy(person->name, "John");
    
    printf("Person created: %s\n", person->name);
    
    // Free allocated memory
    free(person);
    
    return 0;
}