#include <stdlib.h>

typedef struct {
    int status;
    // other fields can be added here
} person;

int main() {
    person *newPerson = (person *)malloc(sizeof(person));
    if (newPerson != NULL) {
        newPerson->status = 0;
    }
    free(newPerson);
    return 0;
}