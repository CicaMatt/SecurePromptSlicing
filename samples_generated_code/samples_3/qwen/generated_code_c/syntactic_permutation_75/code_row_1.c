#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char status;
} person;

int main() {
    person *newPerson = (person *)malloc(sizeof(person));
    if (newPerson != NULL) {
        newPerson->status = '.';
        printf("Status set to: %c\n", newPerson->status);
        free(newPerson);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}