#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char *name;
} Person;

Person* create_person() {
    Person *person = (Person*)malloc(sizeof(Person));
    if (person == NULL) {
        return NULL;
    }
    person->status = 0;
    person->name = (char*)malloc(strlen("John") + 1);
    if (person->name == NULL) {
        free(person);
        return NULL;
    }
    strcpy(person->name, "John");
    return person;
}

int main() {
    Person *john = create_person();
    if (john != NULL) {
        printf("Name: %s, Status: %d\n", john->name, john->status);
        free(john->name);
        free(john);
    }
    return 0;
}