#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int status;
    char name[50];
} Person;

Person* create_person() {
    Person *new_person = (Person*)malloc(sizeof(Person));
    if (new_person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    new_person->status = 0;
    strcpy(new_person->name, "John");
    return new_person;
}

int main() {
    Person *person = create_person();
    printf("Status: %d\n", person->status);
    printf("Name: %s\n", person->name);

    free(person);
    return 0;
}