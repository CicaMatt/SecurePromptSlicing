#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
} Person;

Person* create_person() {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_person->status = 0;
    return new_person;
}

int main() {
    Person *p = create_person();
    printf("Status: %d\n", p->status);
    
    free(p); // Free the allocated memory
    return 0;
}