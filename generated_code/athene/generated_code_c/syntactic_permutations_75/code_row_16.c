#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
} Person;

int main() {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p != NULL) {
        memset(p, 0, sizeof(Person));
    }
    free(p);
    return 0;
}