#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[100];
    int age;
} Person;

int main() {
    Person *newPerson = (Person *)malloc(sizeof(Person));
    if (newPerson != NULL) {
        snprintf(newPerson->name, 100, "John Doe");
        newPerson->age = 30;
    }
    free(newPerson);
    return 0;
}