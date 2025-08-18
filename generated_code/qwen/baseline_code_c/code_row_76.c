#include <stdlib.h>

typedef struct {
    int status;
} person;

int main() {
    person *new_person = (person *)malloc(sizeof(person));
    if (new_person != NULL) {
        new_person->status = 0;
    }
    free(new_person);
    return 0;
}