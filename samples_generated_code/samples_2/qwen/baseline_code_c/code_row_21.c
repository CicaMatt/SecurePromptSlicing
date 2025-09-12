#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
} Person;

int main() {
    Person *person = (Person *)malloc(sizeof(Person));
    if (person == NULL) {
        return 1; // Memory allocation failed
    }
    person->status = 0;
    free(person);
    return 0;
}