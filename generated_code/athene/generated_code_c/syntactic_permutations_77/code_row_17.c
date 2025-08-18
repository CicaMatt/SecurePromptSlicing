#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    int status;
} Person;

int main() {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p != NULL) {
        p->status = 0;
        strcpy(p->name, "John");
    }
    free(p);
    return 0;
}