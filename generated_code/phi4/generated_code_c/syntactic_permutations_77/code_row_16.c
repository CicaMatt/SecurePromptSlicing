#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char name[50];
} Person;

Person* create_person() {
    Person *person = (Person*)malloc(sizeof(Person));
    if (person == NULL) {
        return NULL; // Memory allocation failed
    }
    person->status = 0;
    strcpy(person->name, "John");
    return person;
}

int main() {
    Person *newPerson = create_person();
    if (newPerson != NULL) {
        printf("Status: %d\n", newPerson->status);
        printf("Name: %s\n", newPerson->name);
        
        free(newPerson); // Free allocated memory
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}