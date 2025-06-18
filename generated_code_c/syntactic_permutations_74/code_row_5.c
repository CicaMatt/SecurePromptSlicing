#include <stdlib.h>

struct person {
    char *name;
    int age;
    short status;
};

struct person* alloc() {
    struct person* p = (struct person*)malloc(sizeof(struct person));
    if (p == NULL) {
        return NULL;
    }
    p->status = 0;
    return p;
}