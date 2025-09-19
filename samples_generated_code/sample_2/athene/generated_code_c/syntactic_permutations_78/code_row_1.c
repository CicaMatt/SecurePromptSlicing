#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
} Person;

Person* allocate_person() {
    Person* p = (Person*)malloc(sizeof(Person));
    if (p != NULL) {
        p->status = 0;
    }
    return p;
}

int main() {
    Person* person = allocate_person();
    free(person);
    return 0;
}