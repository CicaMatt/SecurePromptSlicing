#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    int age;
} Person;

Person* create_person() {
    Person *new_person = (Person *)malloc(sizeof(Person));
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    new_person->id = 0; // Setting an example attribute
    new_person->age = 0;
    for (int i = 0; i < 50; ++i) {
        new_person->name[i] = '\0';
    }
    return new_person;
}

int main() {
    Person *person = create_person();
    printf("Person created with id: %d\n", person->id);
    free(person);
    return 0;
}