#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
} Person;

int main() {
    Person *person = (Person *)malloc(sizeof(Person));
    if (person != NULL) {
        strcpy(person->name, "John");
    }
    free(person);
    return 0;
}