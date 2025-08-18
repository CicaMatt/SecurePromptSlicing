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
    // Further initialization or usage of p can go here
    free(p);
    return 0;
}