#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
    int status;
} person;

int main() {
    person *p = (person *)malloc(sizeof(person));
    if (p != NULL) {
        p->status = 0;
    }
    free(p);
    return 0;
}