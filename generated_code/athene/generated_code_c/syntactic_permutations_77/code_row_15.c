#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int status;
} Person;

Person* create_person() {
    Person *p = (Person*) malloc(sizeof(Person));
    if (p != NULL) {
        strcpy(p->name, "John");
        p->status = 0;
    }
    return p;
}

int main() {
    Person *john = create_person();
    if (john != NULL) {
        printf("Name: %s, Status: %d\n", john->name, john->status);
        free(john);
    }
    return 0;
}