#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char name[256];
} Person;

int main() {
    Person *p = (Person *)malloc(sizeof(Person));
    p->status = 0;
    strcpy(p->name, "John");
    free(p);
    return 0;
}