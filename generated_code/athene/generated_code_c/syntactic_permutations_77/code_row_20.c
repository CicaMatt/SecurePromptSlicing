#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
} Person;

int main() {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p != NULL) {
        strcpy(p->name, "John");
    }
    free(p);
    return 0;
}