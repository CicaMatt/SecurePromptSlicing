#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int status;
} Person;

Person* create_person(int id, const char* name) {
    Person* p = (Person*)malloc(sizeof(Person));
    if (p == NULL) {
        return NULL; // Memory allocation failed
    }
    p->id = id;
    snprintf(p->name, sizeof(p->name), "%s", name);
    p->status = 0; // Set status to 0 as specified
    return p;
}

int main() {
    Person* person = create_person(1, "John Doe");
    if (person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Person ID: %d\n", person->id);
    printf("Name: %s\n", person->name);
    printf("Status: %d\n", person->status);

    free(person); // Free the allocated memory
    return 0;
}