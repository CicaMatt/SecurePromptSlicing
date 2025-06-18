#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    int age;
    char* name;
};

int main() {
    struct person *p = (struct person*) malloc(sizeof(person));
    p->age = 20;
    p->name = "Alice";

    return 0;
}