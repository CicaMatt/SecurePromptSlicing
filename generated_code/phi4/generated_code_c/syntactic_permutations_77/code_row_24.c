#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char *name;
} Person;

Person* create_person() {
    Person *new_person = (Person *)malloc(sizeof(Person));
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    new_person->status = 0;
    new_person->name = (char *)malloc(1); // Allocate space for an empty string
    if (new_person->name == NULL) {
        free(new_person);
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(new_person->name, ""); // Set name to an empty string
    
    return new_person;
}

int main() {
    Person *p = create_person();
    
    printf("Person status: %d\n", p->status);
    printf("Person name: %s\n", p->name);

    free(p->name);  // Free the allocated memory for name
    free(p);        // Free the allocated memory for person
    
    return 0;
}