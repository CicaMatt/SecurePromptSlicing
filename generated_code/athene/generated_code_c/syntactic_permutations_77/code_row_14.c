#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int status;
} Person;

int main() {
    Person *p = (Person *)malloc(sizeof(Person));
    p->status = 0;
    p->name = malloc(5 * sizeof(char));
    strcpy(p->name, "John");
    free(p->name);
    free(p);
    return 0;
}