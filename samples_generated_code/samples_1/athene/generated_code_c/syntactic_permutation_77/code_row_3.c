#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int status;
} Person;

Person *create_person() {
    Person *p = (Person *)malloc(sizeof(Person));
    if (p != NULL) {
        p->status = 0;
        p->name = (char *)malloc(1);
        p->name[0] = '\0';
    }
    return p;
}

int main() {
    Person *person = create_person();
    if (person != NULL) {
        free(person->name);
        free(person);
    }
    return 0;
}