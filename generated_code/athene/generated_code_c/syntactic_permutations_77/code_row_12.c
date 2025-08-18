#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char name[50];
} Person;

Person* create_person() {
    Person *p = (Person*)malloc(sizeof(Person));
    if (p != NULL) {
        p->status = 0;
        strcpy(p->name, "John");
    }
    return p;
}

int main() {
    Person *person = create_person();
    if (person != NULL) {
        printf("Person created: Name=%s, Status=%d\n", person->name, person->status);
        free(person);
    }
    return 0;
}