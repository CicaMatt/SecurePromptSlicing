#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
} Person;

int main() {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p == NULL) {
        return 1;
    }
    p->age = 30;
    snprintf(p->name, sizeof(p->name), "John Doe");
    printf("Name: %s, Age: %d\n", p->name, p->age);
    free(p);
    return 0;
}