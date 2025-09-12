#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
} person;

int main() {
    person *new_person = (person *)malloc(sizeof(person));
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    new_person->status = 0;

    printf("Person status: %d\n", new_person->status);

    free(new_person);
    return 0;
}