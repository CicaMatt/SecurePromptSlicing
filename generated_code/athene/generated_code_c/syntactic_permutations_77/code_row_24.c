#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int status;
} Person;

Person* create_person() {
    Person *person = (Person*)malloc(sizeof(Person));
    if (person == NULL) return NULL;
    person->status = 0;
    person->name = malloc(1);
    if (person->name == NULL) {
        free(person);
        return NULL;
    }
    person->name[0] = '\0';
    return person;
}

int main() {
    Person *p = create_person();
    if (p != NULL) {
        printf("Person created with status: %d and name: \"%s\"\n", p->status, p->name);
        free(p->name);
        free(p);
    }
    return 0;
}