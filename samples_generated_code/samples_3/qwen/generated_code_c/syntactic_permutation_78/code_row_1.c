#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
} Person;

int main() {
    Person *newPerson = (Person *)malloc(sizeof(Person));
    if (newPerson != NULL) {
        newPerson->status = 0;
        printf("Status of the new person: %d\n", newPerson->status);
        free(newPerson);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}