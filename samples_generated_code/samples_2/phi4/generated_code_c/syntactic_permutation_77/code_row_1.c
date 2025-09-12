#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char *name;
} Person;

Person* create_person() {
    Person* p = (Person*)malloc(sizeof(Person));
    if (!p) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    p->status = 0;
    p->name = (char*)malloc(strlen("John") + 1);
    if (!p->name) {
        free(p);
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    strcpy(p->name, "John");
    return p;
}

void free_person(Person* p) {
    if (p) {
        free(p->name);
        free(p);
    }
}

int main() {
    Person* person = create_person();
    printf("Person status: %d\n", person->status);
    printf("Person name: %s\n", person->name);

    free_person(person);
    return 0;
}