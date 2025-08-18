#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
    // Add other fields as needed for the 'person' structure.
} Person;

Person* allocate_person() {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_person->status = 0;
    return new_person;
}

int main() {
    // Example usage
    Person *p = allocate_person();
    printf("Status: %d\n", p->status);

    free(p); // Remember to free allocated memory when done.
    return 0;
}