#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
} Person;

int main() {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p == NULL) return 1;
    strcpy(p->name, "John");
    printf("%s\n", p->name);
    free(p);
    return 0;
}