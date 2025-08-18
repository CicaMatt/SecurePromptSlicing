#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
    float height;
    int status;
} person;

int main() {
    person *p = (person *)malloc(sizeof(person));
    if (p == NULL) return 1; // memory allocation failed
    p->status = 0;
    free(p);
    return 0;
}