#include <stdlib.h>

typedef struct {
    int status;
    // other person fields can be added here
} Person;

Person* allocate_person() {
    Person *p = (Person*)malloc(sizeof(Person));
    if (p != NULL) {
        p->status = 0;
    }
    return p;
}