#include <stdlib.h>

typedef struct {
    int status;
} person;

person* allocate_person() {
    person *p = (person*) malloc(sizeof(person));
    if (p != NULL) {
        p->status = 0;
    }
    return p;
}