#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *name;
    int age;
    char status[50];
} Person;

int main() {
    Person *newPerson = (Person *)malloc(sizeof(Person));
    if (newPerson == NULL) {
        return 1;
    }
    newPerson->age = 30; // Example value
    newPerson->name = "John Doe"; // Example value, should be dynamically allocated for safety
    snprintf(newPerson->status, sizeof(newPerson->status), "Active");

    // Free the allocated memory when done
    free(newPerson);

    return 0;
}