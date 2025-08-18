#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
} Person;

int main() {
    Person *newPerson = (Person *)malloc(sizeof(Person));
    if (newPerson == NULL) {
        return 1; // Memory allocation failed
    }
    newPerson->status = 0;
    free(newPerson);
    return 0;
}