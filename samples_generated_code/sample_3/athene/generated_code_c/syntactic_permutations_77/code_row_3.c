#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int status;
} Person;

Person* create_person() {
    Person *p = (Person*)malloc(sizeof(Person));
    if (p == NULL) return NULL;
    p->status = 0;
    p->name = (char*)malloc(1);
    if (p->name == NULL) {
        free(p);
        return NULL;
    }
    p->name[0] = '\0';
    return p;
}

int main() {
    Person *person = create_person();
    if (person != NULL) {
        printf("Person created with status: %d and name: \"%s\"\n", person->status, person->name);
        free(person->name);
        free(person);
    }
    return 0;
}