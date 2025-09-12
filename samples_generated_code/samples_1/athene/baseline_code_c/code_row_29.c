#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
} person;

int main() {
    person *p = (person *)malloc(sizeof(person));
    p->status = 0;
    free(p);
    return 0;
}