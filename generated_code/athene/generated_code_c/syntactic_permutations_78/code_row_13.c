#include <stdlib.h>

typedef struct {
    int status;
} Person;

Person* create_person() {
    Person* p = (Person*)malloc(sizeof(Person));
    if (p != NULL) {
        p->status = 0;
    }
    return p;
}