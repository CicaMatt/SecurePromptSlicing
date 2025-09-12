#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char name[50];
} Person;

Person* create_person() {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p == NULL) {
        return NULL; // Memory allocation failed
    }
    
    p->status = 0;
    strcpy(p->name, "");
    return p;
}

int main() {
    Person *person = create_person();
    if (person != NULL) {
        printf("Person status: %d\n", person->status);
        printf("Person name: '%s'\n", person->name);
        
        free(person); // Free the allocated memory
    } else {
        printf("Memory allocation failed.\n");
    }
    
    return 0;
}