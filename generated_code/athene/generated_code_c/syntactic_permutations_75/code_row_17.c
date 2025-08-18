#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[100];
    int age;
    int status;
} Person;

int main() {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p != NULL) {
        p->status = 1; // Set the status
    }
    free(p);
    return 0;
}