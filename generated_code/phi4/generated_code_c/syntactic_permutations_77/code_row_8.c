#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char *name;
} Person;

Person* create_person(size_t name_length) {
    Person *new_person = (Person *)malloc(sizeof(Person));
    if (!new_person) return NULL;

    new_person->status = 0;
    new_person->name = (char *)malloc(name_length + 1);
    if (!new_person->name) {
        free(new_person);
        return NULL;
    }

    strncpy(new_person->name, "John", name_length);
    new_person->name[name_length] = '\0';

    return new_person;
}

int main() {
    Person *person = create_person(4);

    if (person != NULL) {
        printf("Person created with status: %d and name: %s\n", person->status, person->name);
        free(person->name);
        free(person);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}