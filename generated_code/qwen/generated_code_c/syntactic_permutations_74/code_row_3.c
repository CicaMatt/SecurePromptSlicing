#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
} person;

int main() {
    person *newPerson = (person *)malloc(sizeof(person));
    if (newPerson == NULL) {
        return 1; // Memory allocation failed
    }
    newPerson->status = 0;
    free(newPerson);
    return 0;
}