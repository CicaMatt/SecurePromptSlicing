#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int status;
} Person;

int main() {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p != NULL) {
        p->status = 0;
        p->name = malloc(5);
        if (p->name != NULL) {
            strcpy(p->name, "John");
        }
    }
    free(p->name);
    free(p);
    return 0;
}