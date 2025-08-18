#include <stdlib.h>
#include <string.h>

typedef struct {
    int age;
    char name[50];
} Person;

int main() {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p == NULL) return 1;
    memset(p, 0, sizeof(Person));
    free(p);
    return 0;
}