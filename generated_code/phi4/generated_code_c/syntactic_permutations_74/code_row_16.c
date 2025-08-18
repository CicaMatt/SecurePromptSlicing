#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    float height;
    char name[50];
} Person;

int main() {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p == NULL) {
        return 1; // Memory allocation failed
    }

    p->age = 0;
    p->height = 0.0;
    for (int i = 0; i < 50; ++i) {
        p->name[i] = '\0';
    }

    printf("Person created: Age=%d, Height=%.2f, Name='%s'\n", p->age, p->height, p->name);

    free(p);
    return 0;
}