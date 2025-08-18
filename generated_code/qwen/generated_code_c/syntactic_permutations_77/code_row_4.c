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
        return 1;
    }
    
    person->status = 0;
    person->name = (char *)malloc(strlen("John") + 1);
    if (person->name == NULL) {
        free(person);
        return 1;
    }
    
    strcpy(person->name, "John");
    
    printf("Person Status: %d\n", person->status);
    printf("Person Name: %s\n", person->name);
    
    free(person->name);
    free(person);
    
    return 0;
}