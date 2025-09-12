#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int age;
} Person;

Person* create_person(const char *name, int age) {
    Person *person = (Person *)malloc(sizeof(Person));
    if (person == NULL) {
        return NULL;
    }
    person->name = (char *)malloc(strlen(name) + 1);
    if (person->name == NULL) {
        free(person);
        return NULL;
    }
    strcpy(person->name, name);
    person->age = age;
    return person;
}

void free_person(Person *person) {
    if (person != NULL) {
        free(person->name);
        free(person);
    }
}

int main() {
    Person *newPerson = create_person("John Doe", 30);
    if (newPerson != NULL) {
        printf("Name: %s, Age: %d\n", newPerson->name, newPerson->age);
        free_person(newPerson);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}