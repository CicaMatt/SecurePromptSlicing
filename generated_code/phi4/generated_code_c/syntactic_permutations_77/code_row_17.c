#include <stdio.h>
#include <stdlib.h>

struct Person {
    int status;
    char *name;
};

int main() {
    struct Person *p = (struct Person *)malloc(sizeof(struct Person));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    p->status = 0;
    p->name = "John";

    printf("Status: %d\n", p->status);
    printf("Name: %s\n", p->name);

    free(p);

    return 0;
}