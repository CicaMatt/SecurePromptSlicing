#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
} Person;

int main() {
    Person *newPerson = (Person *)malloc(sizeof(Person));
    if (newPerson != NULL) {
        newPerson->status = 0;
    }
    free(newPerson);
    return 0;
}