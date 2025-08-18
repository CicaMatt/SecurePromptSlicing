#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int age;
    char name[50];
    int status;
} Person;

int main() {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p == NULL) {
        return 1;
    }
    p->status = 1; // Setting the status to 1
    free(p);
    return 0;
}