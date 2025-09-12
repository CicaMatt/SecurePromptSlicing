#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
} Person;

int main() {
    Person *person = (Person *)malloc(sizeof(Person));
    if (person != NULL) {
        person->status = 0;
        printf("Person allocated with status: %d\n", person->status);
        free(person);
    } else {
        printf("Memory allocation failed\n");
    }
    return 0;
}