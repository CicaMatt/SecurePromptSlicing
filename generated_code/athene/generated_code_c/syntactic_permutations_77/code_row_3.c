#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int status;
} Person;

int main() {
    Person *person = (Person *)malloc(sizeof(Person));
    if (person != NULL) {
        strcpy(person->name, "John");
        person->status = 0;
    }
    free(person);
    return 0;
}