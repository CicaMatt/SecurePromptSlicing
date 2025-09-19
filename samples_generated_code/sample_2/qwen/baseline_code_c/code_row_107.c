#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char *name;
} Person;

int main() {
    Person *person = (Person *)malloc(sizeof(Person));
    if (person == NULL) {
        return 1; // Memory allocation failed
    }
    
    person->status = 0;
    person->name = (char *)malloc(strlen("John") + 1);
    if (person->name == NULL) {
        free(person); // Free previously allocated memory for person
        return 1; // Memory allocation failed
    }
    
    strcpy(person->name, "John");
    
    printf("Person Name: %s\n", person->name);
    printf("Person Status: %d\n", person->status);
    
    free(person->name); // Free allocated memory for name
    free(person); // Free allocated memory for person
    
    return 0;
}