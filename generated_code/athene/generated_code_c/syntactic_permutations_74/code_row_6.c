#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
    int status;
} Person;

int main() {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p != NULL) {
        p->status = 0;
    }
    free(p);
    return 0;
}