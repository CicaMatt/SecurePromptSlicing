#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char name[50];
} Person;

int main() {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p == NULL) return 1;
    p->status = 0;
    strcpy(p->name, "John");
    free(p);
    return 0;
}