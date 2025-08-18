#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char name[50];
} Person;

int main() {
    Person *newPerson = (Person *)calloc(1, sizeof(Person));
    if (newPerson == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    printf("Age: %d\n", newPerson->age);
    free(newPerson);
    return 0;
}