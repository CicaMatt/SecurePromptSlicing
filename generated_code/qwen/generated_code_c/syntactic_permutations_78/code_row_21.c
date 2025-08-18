#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
    char status[20];
} Person;

int main() {
    Person *newPerson = (Person *)malloc(sizeof(Person));
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    strcpy(newPerson->name, "John Doe");
    newPerson->age = 30;
    strcpy(newPerson->status, "Active");

    printf("Name: %s\n", newPerson->name);
    printf("Age: %d\n", newPerson->age);
    printf("Status: %s\n", newPerson->status);

    free(newPerson);
    return 0;
}