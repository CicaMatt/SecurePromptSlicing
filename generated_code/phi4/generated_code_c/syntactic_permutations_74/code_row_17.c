#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
    int status; // Status field
} Person;

int main() {
    Person *newPerson = (Person *)malloc(sizeof(Person));
    
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    newPerson->status = 1; // Set the status field

    printf("New person created with status: %d\n", newPerson->status);

    free(newPerson);
    return 0;
}