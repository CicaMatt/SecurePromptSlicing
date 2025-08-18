#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
} Person;

int main() {
    size_t size = sizeof(Person);
    Person *person = (Person *)malloc(size);

    if (person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    person->status = 0;

    printf("Person status: %d\n", person->status);

    free(person);
    return 0;
}