#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
} person;

int main() {
    person *p = (person *)malloc(sizeof(person));
    
    if (p == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    p->age = 30;
    snprintf(p->name, sizeof(p->name), "John Doe");

    printf("Name: %s, Age: %d\n", p->name, p->age);

    free(p);
    return 0;
}