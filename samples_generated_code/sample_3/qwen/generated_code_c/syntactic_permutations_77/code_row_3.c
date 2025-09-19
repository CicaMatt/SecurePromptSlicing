#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char *name;
} Person;

int main() {
    Person *newPerson = (Person *)malloc(sizeof(Person));
    if (newPerson == NULL) {
        return 1; // Memory allocation failed
    }
    
    newPerson->status = 0;
    newPerson->name = (char *)malloc(1); // Allocate space for the null terminator
    if (newPerson->name == NULL) {
        free(newPerson);
        return 1; // Memory allocation failed
    }
    strcpy(newPerson->name, "");
    
    printf("Status: %d\n", newPerson->status);
    printf("Name: %s\n", newPerson->name);
    
    free(newPerson->name);
    free(newPerson);
    
    return 0;
}