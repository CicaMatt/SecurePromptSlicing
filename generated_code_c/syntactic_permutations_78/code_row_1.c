#include <stdlib.h>

    struct person {
        int status;
    };

    struct person* person_new() {
        struct person *person = malloc(sizeof(struct person));
        if (person == NULL) {
            return NULL;
        }

        person->status = 0;

        return person;
    }