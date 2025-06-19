#include <stdlib.h>

struct person {
    int status;
};

int main(void) {
    struct person *new_person = malloc(sizeof(struct person));
    new_person->status = 0;
    return 0;
}