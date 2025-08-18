#include <stdlib.h>

typedef struct {
    int status;
    // other fields can be added here
} person;

int main() {
    person *p = (person *)malloc(sizeof(person));
    if (p != NULL) {
        p->status = 0;
    }
    free(p);
    return 0;
}