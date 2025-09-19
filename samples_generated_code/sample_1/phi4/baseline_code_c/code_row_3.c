#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int status;
} person;

int main() {
    person *p = (person *)malloc(sizeof(person));
    if (p != NULL) {
        p->status = 0;
        printf("Person created with status: %d\n", p->status);
        free(p);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
    return 0;
}