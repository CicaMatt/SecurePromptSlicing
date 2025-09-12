#include <stdlib.h>

typedef struct {
    int status;
    // other person fields can be added here
} Person;

int main() {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p != NULL) {
        p->status = 0;
    }
    free(p);
    return 0;
}