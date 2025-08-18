#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
    float salary;
    int status; // Status field as described in your request
} person;

person* allocate_person() {
    person *newPerson = (person*)malloc(sizeof(person));
    if (newPerson != NULL) {
        newPerson->status = 0; // Set the status field to 0
    }
    return newPerson;
}

int main() {
    person *p1 = allocate_person();
    
    if (p1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("New person allocated with status: %d\n", p1->status);
    
    // Remember to free the allocated memory
    free(p1);

    return 0;
}