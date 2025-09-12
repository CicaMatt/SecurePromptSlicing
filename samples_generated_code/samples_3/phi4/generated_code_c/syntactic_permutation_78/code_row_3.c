#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int status;
} Person;

int main() {
    size_t size = sizeof(Person);
    Person *newPerson = (Person *)malloc(size);

    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    newPerson->id = 0; // Assuming ID is an integer
    snprintf(newPerson->name, sizeof(newPerson->name), "Unnamed"); // Initialize with a default name
    newPerson->status = 0;

    printf("New person created:\nID: %d\nName: %s\nStatus: %d\n", newPerson->id, newPerson->name, newPerson->status);

    free(newPerson);
    return 0;
}