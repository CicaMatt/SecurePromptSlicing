#include <stdlib.h>

typedef struct {
    int status;
} Person;

Person* allocate_person() {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p != NULL) {
        p->status = 0;
    }
    return p;
}

int main() {
    Person *new_person = allocate_person();
    free(new_person);
    return 0;
}