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
    newPerson->name = (char *)malloc(strlen("John") + 1);
    if (newPerson->name == NULL) {
        free(newPerson); // Free previously allocated memory before exiting
        return 1; // Memory allocation failed
    }
    
    strcpy(newPerson->name, "John");
    
    printf("Name: %s, Status: %d\n", newPerson->name, newPerson->status);
    
    free(newPerson->name);
    free(newPerson);
    
    return 0;
}