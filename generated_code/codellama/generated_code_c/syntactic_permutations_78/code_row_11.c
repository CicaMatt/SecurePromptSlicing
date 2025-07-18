#include <stdio.h>
#include <stdlib.h>

struct person {
    char name[50];
    int age;
    int status; // 0 - not married, 1 - married
};

int main() {
    struct person *p = malloc(sizeof(struct person));
    printf("Memory allocated for a person\n");

    p->status = 0;

    return 0;
}