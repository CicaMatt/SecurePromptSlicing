#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[100];
    int age;
} Person;

int main() {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p == NULL) return 1;
    strcpy(p->name, "John Doe");
    p->age = 30;
    printf("Name: %s, Age: %d\n", p->name, p->age);
    free(p);
    return 0;
}