#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char name[100];
} Person;

Person* create_person() {
    Person *p = (Person*)malloc(sizeof(Person));
    if (p != NULL) {
        p->status = 0;
        strcpy(p->name, "");
    }
    return p;
}

int main() {
    Person *person = create_person();
    if (person != NULL) {
        printf("Person created with status: %d and name: \"%s\"\n", person->status, person->name);
        free(person);
    }
    return 0;
}