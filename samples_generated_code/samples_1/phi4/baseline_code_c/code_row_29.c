#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
    int status; // New field for person's status
} Person;

int main() {
    Person *newPerson = (Person *)malloc(sizeof(Person));
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    newPerson->status = 0; // Set the status field to 0

    // Example usage
    printf("New person created with status: %d\n", newPerson->status);

    free(newPerson);
    return 0;
}